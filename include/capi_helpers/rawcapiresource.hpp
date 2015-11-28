#pragma once
#include "capiresource.hpp"

template<typename T>
class RawCAPIResource: CAPIResource<T, std::function<void(T*)>>{
private:
    using CAPIRes = CAPIResource<T, std::function<void(T*)>>;
public:
    using CAPIRes::CAPIRes;
    using CAPIRes::get;
    using CAPIRes::reset;

    T *operator()(){ return get(); }
    T const *operator()() const{ return get(); }
};
