#pragma once

#include <cmath>
#include <initializer_list>

#include <vector>
#include <string>
#include <iostream>
#include <functional>
#include <cstdlib>
#include <map>

class CycledIndexer{
    using Number = int;
public:
    CycledIndexer(Number max_val, Number val):
        max_value(max_val), value(fixed(val)){}
public:
    Number max() const{ return max_value; }
    void update_max(Number max){
        max_value = max;
        value = fixed(value);
    }

    void add(int val){ value = fixed(value + val); }
    void sub(int val){ add(-val); }

    void set(int val){ value = fixed(val); }

    CycledIndexer operator+(Number num){ return CycledIndexer(max_value, value + num); }
    CycledIndexer operator-(Number num){ return CycledIndexer(max_value, value - num); }

    CycledIndexer &operator=(Number num){
        set(num);
        return *this;
    }

    CycledIndexer &operator+=(Number num){
        add(num);
        return *this;
    }
    CycledIndexer &operator-=(Number num){
        sub(num);
        return *this;
    }

    CycledIndexer &operator++(){
        add(1);
        return *this;
    }
    CycledIndexer &operator--(){
        sub(1);
        return *this;
    }

    CycledIndexer operator++(int){
        auto result = *this;
        add(1);
        return result;
    }
    CycledIndexer operator--(int){
        auto result = *this;
        sub(1);
        return result;
    }

    operator Number() const{ return value; }
private:
    Number fixed(Number val){
        auto mod = val%max_value;
        return mod<0 ? max_value + mod : mod;
    }
private:
    Number max_value, value;
};

struct MenuItem{
    using Text = std::string;
    using Action = std::function<void()>;

    Text text;
    Action callback;
};

template<typename MenuType>
class MenuSelectionProxyTemplate{
public:
    using Menu = MenuType;
public:
    MenuSelectionProxyTemplate(Menu &menu): menu(menu){}
public:
    operator MenuItem&(){ return menu.items[menu.indexer]; }
    operator const MenuItem&() const{ return menu.items[menu.indexer]; }

    void call(){ static_cast<MenuItem&>(*this).callback(); }

    auto &text(){ return static_cast<MenuItem&>(*this).text; }
    const auto &text() const{ return static_cast<const MenuItem&>(*this).text; }

    void move_up(){ --menu.indexer; }
    void move_down(){ ++menu.indexer; }
private:
    Menu &menu;
};

class Menu{
    using Items = std::vector<MenuItem>;
    using MenuSelectionProxy = MenuSelectionProxyTemplate<Menu>;
    friend MenuSelectionProxy;
public:
    Menu(): indexer(0, 0){}
    Menu(std::initializer_list<MenuItem> items_list):
        items(items_list), indexer(items.size(), 0){}
public:
    void add_item(const MenuItem &item){
        items.push_back(item);
        update_indexer();
    }
    void add_item(MenuItem &&item){
        items.push_back(item);
        update_indexer();
    }

    Items &all_items(){ return items; }
    const Items &all_items() const{ return items; }

    MenuSelectionProxy selection(){ return MenuSelectionProxy(*this); }
    const MenuSelectionProxy selection() const{ return MenuSelectionProxy(const_cast<Menu&>(*this)); }
private:
    void update_indexer(){
        indexer.update_max(items.size());
    }
private:
    Items items;
    CycledIndexer indexer;
};