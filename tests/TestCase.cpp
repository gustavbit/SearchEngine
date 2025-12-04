//Cmake tests go here

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../src/Directorio.hpp"
#include "../doctest.h"

TEST_CASE("Search Engine"){

    Directorio D("/home/gustav/SearchEngineLin/SearchEngine/tests/TestFolder");

    CHECK(D.search("The cat").size() == 0);
}