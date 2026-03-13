#include <catch2/catch_test_macros.hpp>
#include "url_utils.h"

TEST_CASE("extract_host gets host from https URL") {
    REQUIRE(extract_host("https://example.com/path") == "example.com");
}

TEST_CASE("http and https are accepted") {
    REQUIRE(is_http_or_https("http://example.com"));
    REQUIRE(is_http_or_https("https://example.com"));
    REQUIRE_FALSE(is_http_or_https("mailto:test@example.com"));
}

TEST_CASE("make_absolute_url handles root-relative path") {
    auto result = make_absolute_url("https://example.com/page", "/about");
    REQUIRE(result.has_value());
    REQUIRE(*result == "https://example.com/about");
}

TEST_CASE("normalize_url removes trailing slash") {
    REQUIRE(normalize_url("https://example.com/") == "https://example.com");
}