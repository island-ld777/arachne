#pragma once

#include <optional>
#include <string>

struct HttpResponse {
    long status_code = 0;
    std::string content_type;
    std::string body;
};

class HttpClient {
public:
    HttpClient();
    ~HttpClient();

    std::optional<HttpResponse> get(const std::string& url);
};