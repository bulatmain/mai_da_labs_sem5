#include "../suffix_node.hpp"

namespace lab {

    SuffixNode::SuffixNode() 
        :   start(0ul), 
            end(nullptr), 
            suffixLink(nullptr), 
            suffixIndex(limit<u64>::max()) {}

    SuffixNode::SuffixNode(u64 start, U64Ptr end)
        :   start(start), 
            end(end), 
            suffixLink(nullptr), 
            suffixIndex(limit<u64>::max()) {}

    u64 SuffixNode::getStart() const {
        return start;
    }

    u64 SuffixNode::getEnd() const {
        return end ? *end : 0;
    }

    SuffixNode::ChildrenMap& SuffixNode::getChildren() {
        return children;
    }

    SuffixNode::SuffixNodePtr SuffixNode::getSuffixLink() {
        return suffixLink;
    }

    void SuffixNode::setSuffixLink(SuffixNodePtr node) {
        suffixLink = node;
    }

    void SuffixNode::setSuffixIndex(u64 index) {
        suffixIndex = index;
    }

    u64 SuffixNode::getSuffixIndex() const {
        return suffixIndex;
    }
}
