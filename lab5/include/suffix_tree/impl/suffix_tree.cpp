#include "../suffix_tree.hpp"

#include <queue>
#include <functional>
#include <iostream>

namespace lab {

    SuffixTree::SuffixTree(const std::string& text) 
        :   text(std::make_shared<std::string>(text)), 
            size(text.size()) {
        buildTree(text);
    }

    void SuffixTree::buildTree(const std::string& text) {
        root = std::make_shared<SuffixNode>(
            limit<u64>::max(), 
            std::make_shared<u64>(limit<u64>::max())
        );
        activeNode = root;
        activeEdge = limit<u64>::max();
        activeLength = 0;
        remainingSuffixCount = 0;
        leafEnd = std::make_shared<u64>(limit<u64>::max());
        rootEnd = nullptr;
        splitEnd = nullptr;
        
        for (u64 i = 0; i < size; ++i) {
            extendTree(i);
        }
        
        setSuffixIndexByDFS(root, 0);
    }

    void SuffixTree::extendTree(u64 pos) {
        // Set the end for leaf nodes
        *leafEnd = pos;

        // Number of suffixes to be added
        remainingSuffixCount++;

        SuffixNodePtr lastNewNode = nullptr;

        // Iterate while there are still suffixes to add
        while (remainingSuffixCount > 0) {
            // If active length is 0, the current character is the active edge
            if (activeLength == 0) {
                activeEdge = pos;
            }

            char currentChar = (*text)[pos];
            char activeChar = (*text)[activeEdge];

            // Check if the current character exists in the active node's children
            if (activeNode->getChildren().find(activeChar) == activeNode->getChildren().end()) {
                // No such edge exists, create a new leaf node
                activeNode->getChildren()[activeChar] = std::make_shared<SuffixNode>(pos, leafEnd);

                // Link the last created internal node to this one if necessary
                if (lastNewNode != nullptr) {
                    lastNewNode->setSuffixLink(activeNode);
                    lastNewNode = activeNode->getChildren()[activeChar];
                }
            } else {
                // There is an edge, find the next node
                SuffixNodePtr nextNode = activeNode->getChildren()[activeChar];

                // Check if we are in the middle of an edge
                u64 edgeLength = nextNode->getEnd() - nextNode->getStart() + 1;
                if (activeLength >= edgeLength) {
                    // Move to the next node
                    activeEdge += edgeLength;
                    activeLength -= edgeLength;
                    activeNode = nextNode;
                    continue;
                }

                // The character is already in the edge, rule 3 (extension ends)
                if ((*text)[nextNode->getStart() + activeLength] == currentChar) {
                    // We increment the active length and break
                    activeLength++;
                    if (lastNewNode != nullptr) {
                        lastNewNode->setSuffixLink(activeNode);
                        lastNewNode = nullptr;
                    }
                    break;
                }

                // Split the edge, create a new internal node
                splitEnd = std::make_shared<u64>(nextNode->getStart() + activeLength - 1);
                SuffixNodePtr splitNode = std::make_shared<SuffixNode>(nextNode->getStart(), splitEnd);
                activeNode->getChildren()[activeChar] = splitNode;

                // Create a new leaf node
                splitNode->getChildren()[currentChar] = std::make_shared<SuffixNode>(pos, leafEnd);

                // Adjust the next node's start position
                nextNode->start += activeLength;
                splitNode->getChildren()[(*text)[nextNode->start]] = nextNode;

                // Link last internal node to the new split node
                if (lastNewNode != nullptr) {
                    lastNewNode->setSuffixLink(splitNode);
                }
                lastNewNode = splitNode;
            }

            // Decrement the remaining suffix count
            remainingSuffixCount--;

            // Update the active point
            if (activeNode == root && activeLength > 0) {
                activeLength--;
                activeEdge = pos - remainingSuffixCount + 1;
            } else if (activeNode != root) {
                activeNode = activeNode->getSuffixLink() ? activeNode->getSuffixLink() : root;
            }
        }
    }

    // Depth-First Search to assign suffix indices to each leaf node
    void SuffixTree::setSuffixIndexByDFS(SuffixNode::SuffixNodePtr node, u64 labelHeight) {
        if (!node) return;

        // If it's a leaf, assign the suffix index
        if (node->getChildren().empty()) {
            u64 suffixIndex = size - labelHeight;
            node->setSuffixIndex(suffixIndex); // Correctly setting the suffix index
            return;
        }

        // Traverse all children
        for (auto& [key, child] : node->getChildren()) {
            setSuffixIndexByDFS(child, labelHeight + (child->getEnd() - child->getStart() + 1));
        }
    }

    // Searches for a pattern in the suffix tree
    bool SuffixTree::searchPattern(const std::string& pattern) {
        SuffixNodePtr currentNode = root; // Start from the root node
        u64 patternIndex = 0;             // Track the current index of the pattern

        // Traverse while there are characters left in the pattern
        while (patternIndex < pattern.size()) {
            char currentChar = pattern[patternIndex];

            // Check if the current character exists in the current node's children
            if (currentNode->getChildren().find(currentChar) == currentNode->getChildren().end()) {
                // The current character is not found among the children, pattern does not exist
                return false;
            }

            // Move to the next node
            SuffixNodePtr nextNode = currentNode->getChildren()[currentChar];
            u64 edgeStart = nextNode->getStart();
            u64 edgeEnd = nextNode->getEnd();

            // Compare the pattern characters with the edge characters
            for (u64 i = 0; i <= (edgeEnd - edgeStart) && patternIndex < pattern.size(); ++i) {
                // If characters don't match, pattern is not found
                if ((*text)[edgeStart + i] != pattern[patternIndex]) {
                    return false;
                }
                patternIndex++; // Move to the next character in the pattern
            }

            // Move to the next node in the tree
            currentNode = nextNode;
        }

        // If the entire pattern has been successfully traversed, it exists in the text
        return true;
    }

    std::string SuffixTree::findLCS(const std::string& s1, const std::string& s2) {
        std::string combinedString = s1 + "#" + s2 + "$";
        buildTree(combinedString);
        
        u64 maxLength = 0;
        u64 maxEndIndex = 0;
        u64 splitPoint = s1.size();

        findLCSUtil(root, 0, maxLength, maxEndIndex, splitPoint);

        // Boundary check to prevent out-of-bounds errors
        if (maxEndIndex + 1 < maxLength || maxEndIndex >= combinedString.size()) {
            return ""; // No valid LCS found or invalid indices
        }

        return combinedString.substr(maxEndIndex - maxLength + 1, maxLength);
    }


    void SuffixTree::findLCSUtil(
        SuffixNodePtr node, 
        u64 depth, 
        u64& maxLength, 
        u64& maxEndIndex, 
        u64 splitPoint
    ) {
        if (!node) return;

        bool containsS1Suffix = false;
        bool containsS2Suffix = false;

        if (!node->getChildren().empty()) {
            // Traverse children to gather information
            for (auto& [key, child] : node->getChildren()) {
                findLCSUtil(
                    child, 
                    depth + (child->getEnd() - child->getStart() + 1), 
                    maxLength, 
                    maxEndIndex, 
                    splitPoint
                );
                
                // Gather S1/S2 suffix information from child nodes
                auto index = child->getSuffixIndex();
                if (index == limit<u64>::max()) {
                    continue;
                } else if (index < splitPoint) {
                    containsS1Suffix = true;
                } else if (index >= splitPoint) {
                    containsS2Suffix = true;
                }
            }
        }

        // Update the LCS properties if this node contains both S1 and S2 suffixes
        if (containsS1Suffix && containsS2Suffix && depth > maxLength) {
            maxLength = depth;
            maxEndIndex = node->getEnd();
        }
    }


    std::ostream& operator<<(std::ostream& os, const SuffixTree& tree) {
        std::function<void(SuffixTree::SuffixNodePtr, int)> printTree;
        
        auto text = tree.text;

        printTree = [&](SuffixTree::SuffixNodePtr node, u8 depth) {
            if (node == nullptr) return;

            if (node->getStart() != limit<u64>::max()) {  // Skip root node
                os << std::string(depth * 2, ' ') 
                << text->substr(node->getStart(), node->getEnd() - node->getStart() + 1)
                << (node->getChildren().empty() ? " [" + std::to_string(node->getSuffixIndex()) + "]" : "") 
                << "\n";
            }

            for (const auto &child : node->getChildren()) {
                printTree(child.second, depth + 1);
            }
        };

        printTree(tree.root, 0);
        return os;
    }

}
