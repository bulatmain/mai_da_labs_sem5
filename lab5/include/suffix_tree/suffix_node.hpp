#ifndef SUFFIX_NODE_HPP
#define SUFFIX_NODE_HPP

#include "../type_aliases.hpp"
#include <map>
#include <memory>

namespace lab {

    // Forward declaration of SuffixTree
    class SuffixTree;

    // SuffixNode class representing a node in the suffix tree
    class SuffixNode {
    public:
        using SuffixNodePtr = std::shared_ptr<SuffixNode>;
        using ChildrenMap = std::map<char, SuffixNodePtr>;

        // Constructors
        SuffixNode();
        SuffixNode(u64 start, U64Ptr end);

        // Node properties
        u64 getStart() const;
        u64 getEnd() const;
        ChildrenMap& getChildren();
        SuffixNodePtr getSuffixLink();
        void setSuffixLink(SuffixNodePtr node);

        // Suffix Index
        void setSuffixIndex(u64 index);
        u64 getSuffixIndex() const;

    private:
        u64 start;
        U64Ptr end;
        ChildrenMap children;
        SuffixNodePtr suffixLink; // Link to another node in the tree
        u64 suffixIndex;          // Suffix index for leaf nodes (default: -1 if not a leaf)

        friend SuffixTree;
    };
}

#endif // SUFFIX_NODE_HPP
