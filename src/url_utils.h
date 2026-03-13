#pragma once

#include <optional>
#include <string>

std::string extract_host(const std::string& url);
bool is_http_or_https(const std::string& url);
bool is_same_host(const std::string& host, const std::string& url);
std::optional<std::string> make_absolute_url(const std::string& base_url, const std::string& link);
std::string normalize_url(const std::string& url);