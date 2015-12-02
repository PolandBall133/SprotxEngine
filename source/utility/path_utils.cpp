#include "utility/path_utils.hpp"

boost::filesystem::path operator+(boost::filesystem::path p, const std::string &val){
    return p.append(val);
}
