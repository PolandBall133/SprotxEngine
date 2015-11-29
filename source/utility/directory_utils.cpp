#include "utility/directory_utils.hpp"

#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/adaptor/filtered.hpp>

using namespace std;

vector<boost::filesystem::path> directories_in(const boost::filesystem::path &p){
    using namespace boost::filesystem;
    using namespace boost::adaptors;
    vector<path> paths = {directory_iterator(p),{}};
    vector<path> result;
    boost::copy(paths | filtered([](const path &p){ return is_directory(p); }),
                back_inserter(result));
    return result;
}

boost::filesystem::path deep_locate_directory(
    boost::filesystem::path current_path,
    const std::string &dir_name,
    int lvl){
    if(lvl < 0) return "";
    auto p = current_path;
    p.append(dir_name);

    auto directories = directories_in(current_path);
    auto result = boost::find(directories, p);
    if(result != end(directories))
        return *result;
    for(const auto &directory : directories){
        auto result = deep_locate_directory(directory, dir_name, lvl - 1);
        if(result != "")
            return result;
    }
    return "";
}
boost::filesystem::path greedy_locate_directory(const std::string &dir_name){
    using namespace boost::filesystem;
    return deep_locate_directory("../", dir_name, 3);
}

