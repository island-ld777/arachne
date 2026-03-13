cmake_minimum_required(VERSION 3.16)
project(arachne LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CURL REQUIRED)

add_executable(arachne
    src/main.cpp
    src/crawler.cpp
    src/http_client.cpp
    src/link_extractor.cpp
    src/url_utils.cpp
)

target_include_directories(arachne PRIVATE src)
target_link_libraries(arachne PRIVATE CURL::libcurl)

# --- TEST SETUP ---
include(CTest)
enable_testing()

include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.13.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(arachne_tests
    tests/test_url_utils.cpp
    # tests/test_link_extractor.cpp
    src/url_utils.cpp
    # src/link_extractor.cpp
)

target_include_directories(arachne_tests PRIVATE src)
target_link_libraries(arachne_tests PRIVATE Catch2::Catch2WithMain)

include(${catch2_SOURCE_DIR}/extras/Catch.cmake)
catch_discover_tests(arachne_tests)
