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