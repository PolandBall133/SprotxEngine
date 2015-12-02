#include "game/example_fun/snake/fruits_manager.hpp"

#include <random>
#include <boost/thread/locks.hpp>
#include <boost/log/trivial.hpp>
using namespace std;
using namespace boost;

bool operator==(const FruitsManager::Fruit &fruit, const FruitsManager::Fruit &other){
    return fruit.x == other.x && fruit.y == other.y;
}

FruitsManager::FruitsManager(Limiter l, size_t fruits_count_limit, Time spawn_delay):
    limiter(l),
    max_fruits(fruits_count_limit),
    delay(spawn_delay),

    spawning_thread([this]{
        default_random_engine gen;
        using Distro = uniform_int<int>;
        Distro distro;

        while(true){
            Fruit fruit;

            fruit.x = distro(gen, Distro::param_type(limiter.min_x, limiter.max_x));
            fruit.y = distro(gen, Distro::param_type(limiter.min_y, limiter.max_y));

            add(fruit);
            try{
                boost::this_thread::sleep_for(delay);
            }
            catch(const boost::thread_interrupted &){
                break;
            }
        }
    })
{}

void FruitsManager::add(const Fruit &fruit){
    WriterLock lock(mtx);
    BOOST_LOG_TRIVIAL(info) << "Adding fruit{" << fruit.x << ", " << fruit.y << "}";
    fruits.push_back(fruit);
}

size_t FruitsManager::count() const{
    ReadersLock lock(mtx);
    return fruits.size();
}

FruitsManager::Fruit FruitsManager::at(size_t idx) const{
    ReadersLock lock(mtx);
    return fruits.at(idx);
}

bool FruitsManager::contains(const Fruit &fruit) const{
    ReadersLock lock(mtx);
    return std::find(std::begin(fruits), std::end(fruits), fruit) != std::end(fruits);
}

void FruitsManager::remove(const Fruit &fruit){
    BOOST_LOG_TRIVIAL(info) << "Removing fruit{" << fruit.x << ", " << fruit.y << "}";
    fruits.erase(std::remove(begin(fruits), end(fruits), fruit), end(fruits));
}