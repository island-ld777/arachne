#include "crawler.h"
#include <iostream>

int main() {
    std::string seed = "https://example.com";
    std::size_t max_pages = 20;

    try {
        Crawler crawler(seed, max_pages);
        crawler.run();
    } catch (const std::exception& ex) {
        std::cerr << "Fatal error: " << ex.what() << '\n';
        return 1;
    }

    return 0;
}