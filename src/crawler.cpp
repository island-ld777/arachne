#include "crawler.h"
#include "http_client.h"
#include "link_extractor.h"
#include "url_utils.h"

#include <iostream>

Crawler::Crawler(std::string seed_url, std::size_t max_pages)
    : seed_url_(std::move(seed_url)),
      seed_host_(extract_host(seed_url_)),
      max_pages_(max_pages) {
    frontier_.push(seed_url_);
}

bool Crawler::should_visit(const std::string& url) const {
    if (url.empty()) return false;
    if (!is_http_or_https(url)) return false;

    //TODO: Set up a flag to allow crawling other hosts
    if (!is_same_host(seed_host_, url)) return false;
    return true;
}

void Crawler::run() {
    HttpClient client;
    std::size_t crawled = 0;

    while (!frontier_.empty() && crawled < max_pages_) {
        std::string url = frontier_.front();
        frontier_.pop();

        if (visited_.find(url) != visited_.end()) {
            std::cout << "Already visited: " << url << '\n';
            continue;
        }

        visited_.insert(url);

        std::cout << "Crawling: " << url << '\n';

        auto response = client.get(url);
        if (!response || response->status_code != 200) {
            std::cout << "  Failed or non-200 response\n";
            continue;
        }

        if (response->content_type.find("text/html") == std::string::npos) {
            std::cout << "  Skipping non-HTML content\n";
            continue;
        }

        ++crawled;

        std::cout << "  Status: " << response->status_code << '\n';
        std::cout << "  Found " << response->body.size() << " bytes\n";
        std::cout << "  Body preview: " << response->body.substr(0, 100) << "...\n";

        auto links = extract_links(response->body);
        for (const auto& raw_link : links) {
            auto absolute = make_absolute_url(url, raw_link);
            if (!absolute.has_value()) {
                continue;
            }

            std::string normalized = normalize_url(*absolute);

            if (should_visit(normalized) && visited_.find(normalized) == visited_.end()) {
                frontier_.push(normalized);
            }
        }
    }

    std::cout << "Done. Crawled " << crawled << " pages.\n";
}