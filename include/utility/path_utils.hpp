#pragma once

#include <boost/filesystem.hpp>
#include <string>

boost::filesystem::path operator+(boost::filesystem::path, const std::string &);
