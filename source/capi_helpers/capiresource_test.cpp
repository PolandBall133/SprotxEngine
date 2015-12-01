#include "Catch.hpp"

#include "capi_helpers/capi_resource.hpp"
#include "capi_helpers/raw_capi_resource.hpp"

TEST_CASE("data_access_test", "[CAPIResource]"){
    auto value1 = 0xbabe, value2 = 0xcaffe;

    CAPIResource<int> resource(new int(value1));
    REQUIRE(*resource == value1);

    *resource = value2;
    REQUIRE(*resource == value2);
}

TEST_CASE("memory_safety_test", "[CAPIResource] #simplified_test"){
    struct Dummy{
        int value;
    };
    size_t fred = 0;
    auto free = [&](Dummy *d){ 
        delete d; 
        fred += 1;
    };

    {
        RawCAPIResource<Dummy> resource(new Dummy{0}, free);
        REQUIRE(fred == 0);
        resource.reset(new Dummy{1});
        REQUIRE(fred == 1);
    }
    REQUIRE(fred == 2);
}