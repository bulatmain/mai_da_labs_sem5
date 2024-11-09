#ifndef SUFFIX_TREE_HPP
#define SUFFIX_TREE_HPP

#include "suffix_node.hpp"
#include "../type_aliases.hpp"
#include <string>
#include <vector>
#include <set>

namespace lab {

    class SuffixTree {
    public:
        using StringPtr = std::shared_ptr<std::string>;
        using SuffixNodePtr = SuffixNode::SuffixNodePtr;

        // Constructors
        SuffixTree(const std::string& text);

        // Public interface
        void buildTree(const std::string& text);
        std::set<u64> searchPattern(const std::string& pattern);
        static std::pair<u64, std::vector<u64>> findLCS(const std::string& s1, const std::string& s2);
        static std::pair<u64, std::set<std::string>> findLCSString(const std::string& s1, const std::string& s2);

    private:
        // Internal helper functions
        void extendTree(u64 pos);
        void setSuffixIndexByDFS(SuffixNodePtr node, u64 labelHeight);
        static void findLCSUtil(
            SuffixNodePtr node, 
            u64 depth, 
            u64& maxLength,
            u64 splitPoint,
            std::map<u64, u64>& nodeCSLengths
        );

        // Tree properties
        StringPtr text;                        // The input string
        SuffixNodePtr root;        // Root of the suffix tree
        SuffixNodePtr activeNode;  // Active node for construction
        u64 activeEdge;
        u64 activeLength;
        u64 remainingSuffixCount;
        U64Ptr leafEnd;
        U64Ptr rootEnd;
        U64Ptr splitEnd;
        u64 size; // Size of the input string

        friend std::ostream& operator<<(std::ostream& os, SuffixTree const& t);

    };

    std::ostream& operator<<(std::ostream& os, SuffixTree const& t);
}

#endif // SUFFIX_TREE_HPP
