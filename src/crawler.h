#pragma once

#include <cstddef>
#include <queue>
#include <string>
#include <unordered_set>

class Crawler {
public:
    Crawler(std::string seed_url, std::size_t max_pages);
    void run();

private:
    std::string seed_url_;
    std::string seed_host_;
    std::size_t max_pages_;

    std::queue<std::string> frontier_;
    std::unordered_set<std::string> visited_;

    bool should_visit(const std::string& url) const;
};