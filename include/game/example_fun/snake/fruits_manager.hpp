#pragma once
#include <boost/thread.hpp>
#include <vector>
#include <boost/chrono.hpp>

#include "limiter.hpp"
class FruitsManager{
public:
    using Time = boost::chrono::seconds;
    struct Fruit{
        int x, y;
        friend bool operator==(const Fruit &fruit, const Fruit &other);
    };

private:
    typedef boost::unique_lock<boost::shared_mutex> WriterLock;
    typedef boost::shared_lock<boost::shared_mutex> ReadersLock;
    mutable boost::shared_mutex mtx;
    std::vector<Fruit> fruits;

    Limiter limiter;
    boost::thread spawning_thread;

    const size_t max_fruits;
    const Time delay;
public:
    FruitsManager(Limiter l, size_t fruits_count_limit, Time spawn_delay);
    void add(const Fruit &);
    size_t count() const;
    Fruit at(size_t idx) const;
    bool contains(const Fruit &fruit) const;
    void remove(const Fruit &fruit);
};