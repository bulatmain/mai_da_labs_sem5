#include <iostream>
#include <set>

#include <suffix_tree/suffix_tree.hpp>

using namespace lab;

int main() {
    std::string text;
    std::getline(std::cin, text);

    SuffixTree tree(text + "$");

    std::string pattern;
    u64 count = 1;
    while (std::getline(std::cin, pattern)) {
        auto indexes = tree.searchPattern(pattern);
        if (!indexes.empty()) {
            std::cout << count << ": ";
            auto i = indexes.begin();
            std::cout << *(i++) + 1;
            while (i != indexes.end()) {
                std::cout  << ", " << *(i++) + 1;
            }
            std::cout << "\n";
        }
        ++count;
    }

    return 0;
}