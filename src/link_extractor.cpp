#include "link_extractor.h"

#include <regex>

std::vector<std::string> extract_links(const std::string& html) {
    std::vector<std::string> links;

    static const std::regex href_regex(R"(href\s*=\s*["']([^"'#]+)["'])",
                                       std::regex::icase);

    auto begin = std::sregex_iterator(html.begin(), html.end(), href_regex);
    auto end = std::sregex_iterator();

    for (auto it = begin; it != end; ++it) {
        links.push_back((*it)[1].str());
    }

    return links;
}