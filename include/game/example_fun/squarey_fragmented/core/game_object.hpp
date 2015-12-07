#pragma once
#include <functional>
#include <boost/utility.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iterator>

#include "game_core/game_engine.hpp"
#include "graphics_core/graphics_engine.hpp"
using std::function;
using Noncopyable = boost::noncopyable;
using String = std::string;

struct GameObject;

struct Vec2{
    double x = 0, y = 0;
};

struct Transform{
    Vec2 position;
};

struct GameObject{
    Transform transform;
    String tag;
};

struct GameObjectsContainer: Noncopyable{
    using GameObjectHolder = std::unique_ptr<GameObject>;
    using GameObjects = std::vector<GameObjectHolder>;
    using GameObjectView = std::reference_wrapper<GameObjectHolder>;
    using GameObjectsView = std::vector<GameObjectView>;
    GameObjects game_objects;

    GameObjectsView find_with_tag(const String &tag){
        GameObjectsView result;
        std::copy_if(game_objects.begin(), game_objects.end(), std::back_inserter(result), [&](auto &item){
            return item->tag == tag;
        });
        return result;
    }

    void register_object(GameObject *game_object){
        game_objects.emplace_back(game_object);
    }
};

struct Script: Noncopyable{
    GameObject *attached_object;
    GameObjectsContainer *objects_container;

    GameEngine *game_engine;
    GraphicsEngine *graphics_engine;

    using Callback = function<void()>;

    Callback pre, step, render, post;

    //todo: boost::param_type or similar
    Script(GameObject *ao, GameObjectsContainer *cont, GameEngine *e, GraphicsEngine *ge):
        attached_object(ao),
        objects_container(cont),
        game_engine(e),
        graphics_engine(ge){}

    template<typename ScriptType>
    static Script *spawn_attached_to(GameObject *object, GameEngine *engine, GraphicsEngine *graphics){
        return new ScriptType(object, nullptr, engine, graphics);
    }
};
#define SCRIPT_INIT_METHODS(ScriptName, mpre, mstep, mrender, mpost) \
ScriptName(GameObject *_1, GameObjectsContainer *_2, GameEngine *_3, GraphicsEngine *_4): \
    Script(_1, _2, _3, _4) \
{ \
    Script::pre = std::bind(&ScriptName::mpre, std::ref(*this)); \
    Script::step = std::bind(&ScriptName::mstep, std::ref(*this)); \
    Script::render = std::bind(&ScriptName::mrender, std::ref(*this)); \
    Script::post = std::bind(&ScriptName::mpost, std::ref(*this)); \
}

//todo: keyboard handling (which calls every scripts handler)
struct ScriptsContainer: Noncopyable{
    using ScriptHolder = std::unique_ptr<Script>;
    using Scripts = std::vector<ScriptHolder>;
    using ScriptView = std::reference_wrapper<ScriptHolder>;
    using ScriptsView = std::vector<ScriptView>;

    GameObjectsContainer *game_objects;
    Scripts scripts;

    void register_script(Script *script){
        script->objects_container = game_objects;
        if(script->pre)
            script->pre();
        scripts.emplace_back(script);
    }

    void update_all(){
        for(auto &script : scripts)
            if(script->step)
                script->step();
    }

    void render_all(){
        for(auto &script : scripts)
            if(script->render)
                script->render();
    }

    void unregister_all(){
        for(auto &script : scripts){
            if(script->post){
                script->post();
                script->post = nullptr;
            }
        }
    }

    ~ScriptsContainer(){
        unregister_all();
    }
};