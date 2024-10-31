#include "suffix_tree/suffix_tree.hpp"
#include <gtest/gtest.h>
#include <limits>

using namespace lab;

// Test fixture for SuffixTree
class SuffixTreeTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize sample text and suffix tree
        sampleText = "abcabxabcd#";
        tree = std::make_unique<SuffixTree>(sampleText);
    }

    std::unique_ptr<SuffixTree> tree;
    std::string sampleText;
};

// Test cases for searchPattern
TEST_F(SuffixTreeTest, PatternExistsAtBeginning) {
    EXPECT_TRUE(tree->searchPattern("abc"));
}

TEST_F(SuffixTreeTest, PatternExistsInMiddle) {
    EXPECT_TRUE(tree->searchPattern("bxa"));
}

TEST_F(SuffixTreeTest, PatternExistsAtEnd) {
    EXPECT_TRUE(tree->searchPattern("abcd"));
}

TEST_F(SuffixTreeTest, NonExistentPattern) {
    EXPECT_FALSE(tree->searchPattern("xbca"));
}

TEST_F(SuffixTreeTest, PatternLongerThanText) {
    EXPECT_FALSE(tree->searchPattern("abcabxabcdabc"));
}

TEST_F(SuffixTreeTest, SingleCharacterPatternExists) {
    EXPECT_TRUE(tree->searchPattern("a"));
}

TEST_F(SuffixTreeTest, SingleCharacterPatternNotExist) {
    EXPECT_FALSE(tree->searchPattern("z"));
}

TEST_F(SuffixTreeTest, EmptyPatternShouldReturnTrue) {
    EXPECT_TRUE(tree->searchPattern(""));
}

// Test cases for findLCS
TEST(SuffixTreeFindLCSTest, LCSExistsBetweenTwoStrings) {
    std::string s1 = "banana";
    std::string s2 = "bandana";
    SuffixTree tree(s1 + "#" + s2 + "$");
    EXPECT_EQ(tree.findLCS(s1, s2), "ana");
}

TEST(SuffixTreeFindLCSTest, NoCommonSubstring) {
    std::string s1 = "abc";
    std::string s2 = "xyz";
    SuffixTree tree(s1 + "#" + s2 + "$");
    EXPECT_EQ(tree.findLCS(s1, s2), "");
}

TEST(SuffixTreeFindLCSTest, LCSIsFullString) {
    std::string s1 = "apple";
    std::string s2 = "apple";
    SuffixTree tree(s1 + "#" + s2 + "$");
    EXPECT_EQ(tree.findLCS(s1, s2), "apple");
}

TEST(SuffixTreeFindLCSTest, LCSWithPartialOverlap) {
    std::string s1 = "abcdef";
    std::string s2 = "defabc";
    SuffixTree tree(s1 + "#" + s2 + "$");
    EXPECT_EQ(tree.findLCS(s1, s2), "abc");
}

TEST(SuffixTreeFindLCSTest, LCSLongOverlap) {
    std::string s1 = "aabcaabc";
    std::string s2 = "abcaabc";
    SuffixTree tree(s1 + "#" + s2 + "$");
    EXPECT_EQ(tree.findLCS(s1, s2), "abcaabc");
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}