#pragma once

#include <boost/filesystem.hpp>
#include <string>
#include <vector>

std::vector<boost::filesystem::path> directories_in(const boost::filesystem::path &p);

boost::filesystem::path deep_locate_directory(
    boost::filesystem::path current_path,
    const std::string &dir_name,
    int lvl);

boost::filesystem::path greedy_locate_directory(const std::string &dir_name);
