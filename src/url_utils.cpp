#include "url_utils.h"

#include <algorithm>

std::string extract_host(const std::string& url) {
    auto scheme_pos = url.find("://");
    if (scheme_pos == std::string::npos) return "";

    auto host_start = scheme_pos + 3;
    auto host_end = url.find('/', host_start);

    if (host_end == std::string::npos) {
        return url.substr(host_start);
    }

    return url.substr(host_start, host_end - host_start);
}

bool is_http_or_https(const std::string& url) {
    return url.rfind("http://", 0) == 0 || url.rfind("https://", 0) == 0;
}

bool is_same_host(const std::string& host, const std::string& url) {
    return extract_host(url) == host;
}

std::optional<std::string> make_absolute_url(const std::string& base_url, const std::string& link) {
    if (link.empty()) return std::nullopt;

    if (is_http_or_https(link)) {
        return link;
    }

    if (link[0] == '/') {
        auto scheme_pos = base_url.find("://");
        if (scheme_pos == std::string::npos) return std::nullopt;

        auto host_start = scheme_pos + 3;
        auto host_end = base_url.find('/', host_start);

        std::string origin = (host_end == std::string::npos)
            ? base_url
            : base_url.substr(0, host_end);

        return origin + link;
    }

    return std::nullopt;
}

std::string normalize_url(const std::string& url) {
    std::string result = url;

    if (!result.empty() && result.back() == '/') {
        result.pop_back();
    }

    return result;
}