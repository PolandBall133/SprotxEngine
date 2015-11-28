#pragma once

#include <boost/utility.hpp>
#include <memory>
#include <functional>

template<typename T, class Deleter = std::default_delete<T>>
class CAPIResource: boost::noncopyable{
private:
    using handle_type = std::unique_ptr<T, Deleter>;
    std::unique_ptr<T, Deleter> data_handle;
public:
    template<typename IP>
    CAPIResource(IP instance_provider, Deleter &&deleter = Deleter()):
        data_handle({instance_provider(), deleter}){}

    T *get(){ return data_handle.get(); }
    T const *get() const{ return data_handle.get(); }

    T *operator()(){ return get(); }
    T const *operator()() const{ return get(); }
};