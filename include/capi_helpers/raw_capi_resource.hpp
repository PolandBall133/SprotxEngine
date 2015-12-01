#pragma once
#include <functional>

#include "capi_resource.hpp"

template<typename T>
using RawCAPIResource = CAPIResource<T, std::function<void(T*)>>;