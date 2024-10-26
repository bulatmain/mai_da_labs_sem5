#ifndef SUFFIX_TREE_HPP
#define SUFFIX_TREE_HPP

#include "suffix_node.hpp"
#include "../type_aliases.hpp"
#include <string>
#include <vector>

namespace lab {

    class SuffixTree {
    public:
        using StringPtr = std::shared_ptr<std::string>;
        using SuffixNodePtr = SuffixNode::SuffixNodePtr;

        // Constructors
        SuffixTree(const std::string& text);

        // Public interface
        void buildTree(const std::string& text);
        bool searchPattern(const std::string& pattern);
        std::string findLCS(const std::string& S1, const std::string& S2);

    private:
        // Internal helper functions
        void extendTree(u64 pos);
        void setSuffixIndexByDFS(SuffixNodePtr node, u64 labelHeight);
        void findLCSUtil(SuffixNodePtr node, u64 depth, u64& maxLength, u64& maxEndIndex, u64 splitPoint);

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

    };
}

#endif // SUFFIX_TREE_HPP
