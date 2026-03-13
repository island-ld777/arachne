#include "http_client.h"

#include <curl/curl.h>

#include <iostream>

namespace {
size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp) {
    std::size_t total = size * nmemb;
    auto* buffer = static_cast<std::string*>(userp);
    buffer->append(static_cast<char*>(contents), total);
    return total;
}
}

HttpClient::HttpClient() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

HttpClient::~HttpClient() {
    curl_global_cleanup();
}

std::optional<HttpResponse> HttpClient::get(const std::string& url) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        return std::nullopt;
    }

    HttpResponse response;
    std::string body;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "cpp-learning-crawler/0.1");
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 15L);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        curl_easy_cleanup(curl);
        return std::nullopt;
    }

    char* content_type = nullptr;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response.status_code);
    curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &content_type);

    response.body = std::move(body);
    if (content_type) {
        response.content_type = content_type;
    }

    curl_easy_cleanup(curl);
    return response;
}