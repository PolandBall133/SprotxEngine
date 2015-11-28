#include "Catch.hpp"

#include "capi_helpers/capiresource.hpp"
#include "capi_helpers/rawcapiresource.hpp"

TEST_CASE("data_access_test", "[CAPIResource]"){
    auto value1 = 0xbabe, value2 = 0xcaffe;

    CAPIResource<int> resource(new int(value1));
    REQUIRE(*resource() == value1);

    *resource() = value2;
    REQUIRE(*resource() == value2);
}

TEST_CASE("memory_safety_test", "[CAPIResource] #simplified_test"){
    struct Dummy{
        int value;
    };
    bool fred = false;
    auto free = [&](Dummy *d){ 
        delete d; 
        fred = true;
    };

    {
        RawCAPIResource<Dummy> resource(new Dummy{0}, free);
        REQUIRE(fred == false);
    }
    REQUIRE(fred == true);
}