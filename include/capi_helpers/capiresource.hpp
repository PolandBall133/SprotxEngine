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
    CAPIResource(T *instance, Deleter &&deleter = Deleter()):
        data_handle({instance, deleter}){}

    void reset(T *instance){ data_handle.reset(instance); }
    T *get(){ return data_handle.get(); }
    T const *get() const{ return data_handle.get(); }

    T *operator()(){ return get(); }
    T const *operator()() const{ return get(); }
};