#pragma once

#include <boost/utility.hpp>
#include <memory>
#include <functional>

template<typename T, class Deleter = std::default_delete<T>>
using CAPIResource = std::unique_ptr<T, Deleter>;