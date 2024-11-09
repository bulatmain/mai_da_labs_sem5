#include "suffix_tree/suffix_tree.hpp"
#include <gtest/gtest.h>
#include <limits>

using namespace lab;

#define TEST_SEARCH_PATTERN
#ifndef TEST_SEARCH_PATTERN
#define TEST_SEARCH_PATTERN

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
    EXPECT_EQ(tree->searchPattern("abc"), std::set<u64>{});
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

#endif

#ifndef TEST_LCS
#define TEST_LCS

void testLCS(
    std::string const& s1, 
    std::string const& s2,
    u64 length,
    std::initializer_list<u64> indexes
) {
    auto [_length, _indexes] = SuffixTree::findLCS(s1, s2);
    EXPECT_EQ(_length, length);
    EXPECT_EQ(
        _indexes, 
        std::vector<u64>(indexes)
    );
}

// Test cases for findLCS
TEST(SuffixTreeFindLCSTest, LCSExistsBetweenTwoStrings) {
    std::string s1 = "banana";
    std::string s2 = "bandana";
    testLCS(s1, s2, 3, {0, 1});
}

TEST(SuffixTreeFindLCSTest, NoCommonSubstring) {
    std::string s1 = "abc";
    std::string s2 = "xyz";
    testLCS(s1, s2, 0, {});
}

TEST(SuffixTreeFindLCSTest, LCSIsFullString) {
    std::string s1 = "apple";
    std::string s2 = "apple";
    testLCS(s1, s2, 5, {0});
}

TEST(SuffixTreeFindLCSTest, LCSWithPartialOverlap) {
    std::string s1 = "abcdef";
    std::string s2 = "defabc";
    testLCS(s1, s2, 3, {0, 3});
}

TEST(SuffixTreeFindLCSTest, LCSLongOverlap) {
    std::string s1 = "aabcaabc";
    std::string s2 = "abcaabc";
    testLCS(s1, s2, 7, {1});
}

// Additional test cases for findLCS
TEST(SuffixTreeFindLCSTest, LCSOneCharacterMatch) {
    std::string s1 = "a";
    std::string s2 = "a";
    testLCS(s1, s2, 1, {0});
}

TEST(SuffixTreeFindLCSTest, LCSNoMatchSingleCharacters) {
    std::string s1 = "a";
    std::string s2 = "b";
    testLCS(s1, s2, 0, {});
}

TEST(SuffixTreeFindLCSTest, LCSNoMatchEmptyString) {
    std::string s1 = "";
    std::string s2 = "nonempty";
    testLCS(s1, s2, 0, {});
}

TEST(SuffixTreeFindLCSTest, LCSOneStringEmpty) {
    std::string s1 = "nonempty";
    std::string s2 = "";
    testLCS(s1, s2, 0, {});
}

TEST(SuffixTreeFindLCSTest, LCSDifferentCaseSensitivity) {
    std::string s1 = "abcdef";
    std::string s2 = "ABCDEF";
    testLCS(s1, s2, 0, {}); // assuming case-sensitive comparison
}

TEST(SuffixTreeFindLCSTest, LCSMultipleMatchesSameLength) {
    std::string s1 = "abababab";
    std::string s2 = "babababa";
    testLCS(s1, s2, 7, {0, 1}); // longest matches could start at index 0 or 1
}

TEST(SuffixTreeFindLCSTest, LCSLongRepeatingSubstring) {
    std::string s1 = "aaaaaaa";
    std::string s2 = "aaaa";
    testLCS(s1, s2, 4, {0});
}

TEST(SuffixTreeFindLCSTest, LCSEqualStringsDifferentLengths) {
    std::string s1 = "abcde";
    std::string s2 = "abc";
    testLCS(s1, s2, 3, {0});
}

TEST(SuffixTreeFindLCSTest, LCSLongerInMiddle) {
    std::string s1 = "xyzabcdxyz";
    std::string s2 = "pqrabcdpqr";
    testLCS(s1, s2, 4, {3});
}

TEST(SuffixTreeFindLCSTest, LCSMixedAlphaNumeric) {
    std::string s1 = "abc123def";
    std::string s2 = "123ghi";
    testLCS(s1, s2, 3, {3});
}

TEST(SuffixTreeFindLCSTest, LCSWithSpecialCharacters) {
    std::string s1 = "hello|world";
    std::string s2 = "world|hello";
    testLCS(s1, s2, 5, {0, 6});
}

TEST(SuffixTreeFindLCSTest, LCSCommonPrefixOnly) {
    std::string s1 = "commonprefix123";
    std::string s2 = "commonprefix456";
    testLCS(s1, s2, 12, {0});
}

TEST(SuffixTreeFindLCSTest, LCSCommonSuffixOnly) {
    std::string s1 = "123commonsuffix";
    std::string s2 = "456commonsuffix";
    testLCS(s1, s2, 12, {3});
}

TEST(SuffixTreeFindLCSTest, LCSRandomCharacters) {
    std::string s1 = "afhgtc";
    std::string s2 = "bhgtfc";
    testLCS(s1, s2, 3, {2});
}

TEST(SuffixTreeFindLCSTest, LCSLongNoCommon) {
    std::string s1 = "abcdefghijklm";
    std::string s2 = "nopqrstuvwxyz";
    testLCS(s1, s2, 0, {});
}

TEST(SuffixTreeFindLCSTest, LCSEmptyStrings) {
    testLCS("", "", 0, {});
}

// Extensive test cases for findLCS

// Test with large identical strings
TEST(SuffixTreeFindLCSTest, LargeIdenticalStrings) {
    std::string s1(1000, 'a');
    std::string s2(1000, 'a');
    testLCS(s1, s2, 1000, {0});
}

// Test with large strings with no common substring
TEST(SuffixTreeFindLCSTest, LargeNoCommonSubstring) {
    std::string s1(1000, 'a');
    std::string s2(1000, 'b');
    testLCS(s1, s2, 0, {});
}

// Test with long string where LCS is a substring in the middle
TEST(SuffixTreeFindLCSTest, LCSInMiddleOfLongString) {
    std::string s1 = "xyz" + std::string(100, 'a') + "middle" + std::string(100, 'b') + "end";
    std::string s2 = "start" + std::string(100, 'c') + "middle" + std::string(100, 'd') + "xyz";
    testLCS(s1, s2, 6, {103}); // "middle" common substring starts at index 103 in s1
}

// Test with long strings with partial overlapping patterns
TEST(SuffixTreeFindLCSTest, PartialOverlapWithLargeStrings) {
    std::string s1 = "a" + std::string(500, 'b') + "cdef";
    std::string s2 = "b" + std::string(500, 'b') + "cdef";
    testLCS(s1, s2, 504, {1});
}

// Test with alternating character pattern
TEST(SuffixTreeFindLCSTest, AlternatingPatternStrings) {
    std::string s1 = "abababababab";
    std::string s2 = "babababababa";
    testLCS(s1, s2, 11, {0, 1}); // Largest common substring is nearly the full string
}

// Test with palindrome pattern
TEST(SuffixTreeFindLCSTest, PalindromicPattern) {
    std::string s1 = "racecar";
    std::string s2 = "carrace";
    testLCS(s1, s2, 4, {0}); // Longest common substrings start at multiple positions
}

// Test where LCS has special characters and spaces
TEST(SuffixTreeFindLCSTest, SpecialCharactersAndSpaces) {
    std::string s1 = "Hello, World! How are you?";
    std::string s2 = "World! How is everyone?";
    testLCS(s1, s2, 11, {7}); // Longest common substring "World! "
}

// Test with common substring appearing at the start and end
TEST(SuffixTreeFindLCSTest, CommonSubstringAtStartAndEnd) {
    std::string s1 = "prefix_common_suffix";
    std::string s2 = "common";
    testLCS(s1, s2, 6, {7});
}

// Test with overlapping numbers
TEST(SuffixTreeFindLCSTest, OverlappingNumbers) {
    std::string s1 = "123451234512345";
    std::string s2 = "4512345";
    testLCS(s1, s2, 7, {3});
}

// Test with repeated long substring
TEST(SuffixTreeFindLCSTest, LongRepeatedSubstring) {
    std::string s1 = "repeatrepeatrepeatrepeat";
    std::string s2 = "repeatrepeat";
    testLCS(s1, s2, 12, {0}); // "repeatrepeat" appears multiple times in s1
}

// Test with one string fully contained in the other
TEST(SuffixTreeFindLCSTest, OneStringFullyContained) {
    std::string s1 = "thisisaverylongstring";
    std::string s2 = "longstring";
    testLCS(s1, s2, 10, {11});
}

// Test with overlapping symbols
TEST(SuffixTreeFindLCSTest, OverlappingSymbols) {
    std::string s1 = "&&&&";
    std::string s2 = "&&&&&&";
    testLCS(s1, s2, 4, {0});
}

// Test with partial match near end of strings
TEST(SuffixTreeFindLCSTest, PartialMatchNearEnd) {
    std::string s1 = "abcdef12345";
    std::string s2 = "xyz12345";
    testLCS(s1, s2, 5, {6});
}

TEST(SuffixTreeFindLCSTest, LongString) {
    std::string s1 = "We still need to insert the final suffix of the current step, x. Since the active_length component of the active node has fallen to 0, the final insert is made at the root directly. Since there is no outgoing edge at the root node starting with x, we insert a new edge:";
    std::string s2 = "suffix curren compon";
    testLCS(s1, s2, 7, {34, 47, 88});
}

#endif

#ifndef TEST_LCS_STRING
#define TEST_LCS_STRING

void testLCSString(
    std::string const& s1,
    std::string const& s2,
    u64 length,
    std::initializer_list<std::string> lcs
) {
    auto [_length, _lcs] = SuffixTree::findLCSString(s1, s2);
    EXPECT_EQ(_length, length);
    EXPECT_EQ(
        _lcs, 
        std::set<std::string>(lcs)
    );
}

// Extensive test cases for findLCSString

// Test with single common substring
TEST(SuffixTreeFindLCSStringTest, SingleCommonSubstring) {
    std::string s1 = "banana";
    std::string s2 = "bandana";
    testLCSString(s1, s2, 3, {"ana", "ban"});
}

// Test with no common substring
TEST(SuffixTreeFindLCSStringTest, NoCommonSubstring) {
    std::string s1 = "abc";
    std::string s2 = "xyz";
    testLCSString(s1, s2, 0, {});
}

// Test with entire string as LCS
TEST(SuffixTreeFindLCSStringTest, EntireStringAsLCS) {
    std::string s1 = "apple";
    std::string s2 = "apple";
    testLCSString(s1, s2, 5, {"apple"});
}

// Test with partial overlap
TEST(SuffixTreeFindLCSStringTest, PartialOverlap) {
    std::string s1 = "abcdef";
    std::string s2 = "defabc";
    testLCSString(s1, s2, 3, {"abc", "def"});
}

// Test with repeating pattern
TEST(SuffixTreeFindLCSStringTest, RepeatingPattern) {
    std::string s1 = "abababab";
    std::string s2 = "babababa";
    testLCSString(s1, s2, 7, {"abababa", "bababab"});
}

// Test with different case sensitivity
TEST(SuffixTreeFindLCSStringTest, CaseSensitive) {
    std::string s1 = "ABCabc";
    std::string s2 = "abcABC";
    testLCSString(s1, s2, 3, {"ABC", "abc"});
}

// Test with palindromic substrings
TEST(SuffixTreeFindLCSStringTest, PalindromicSubstring) {
    std::string s1 = "racecar";
    std::string s2 = "carrace";
    testLCSString(s1, s2, 4, {"race"});
}

// Test with mixed alphanumeric characters
TEST(SuffixTreeFindLCSStringTest, MixedAlphanumeric) {
    std::string s1 = "abc123def";
    std::string s2 = "xyz123ghi";
    testLCSString(s1, s2, 3, {"123"});
}

// Test with special characters
TEST(SuffixTreeFindLCSStringTest, SpecialCharacters) {
    std::string s1 = "Hello, World!";
    std::string s2 = "Hi, World!";
    testLCSString(s1, s2, 8, {", World!"});
}

// Test with empty strings
TEST(SuffixTreeFindLCSStringTest, EmptyStrings) {
    std::string s1 = "";
    std::string s2 = "";
    testLCSString(s1, s2, 0, {});
}

// Test where one string is empty
TEST(SuffixTreeFindLCSStringTest, OneStringEmpty) {
    std::string s1 = "nonempty";
    std::string s2 = "";
    testLCSString(s1, s2, 0, {});
}

// Test with long repeating substrings
TEST(SuffixTreeFindLCSStringTest, LongRepeatingSubstring) {
    std::string s1 = "repeatrepeatrepeat";
    std::string s2 = "repeatrepeat";
    testLCSString(s1, s2, 12, {"repeatrepeat"});
}

// Test with overlapping numbers
TEST(SuffixTreeFindLCSStringTest, OverlappingNumbers) {
    std::string s1 = "1234512345";
    std::string s2 = "4512345";
    testLCSString(s1, s2, 7, {"4512345"});
}

// Test with common prefix only
TEST(SuffixTreeFindLCSStringTest, CommonPrefixOnly) {
    std::string s1 = "commonprefix123";
    std::string s2 = "commonprefix456";
    testLCSString(s1, s2, 12, {"commonprefix"});
}

// Test with common suffix only
TEST(SuffixTreeFindLCSStringTest, CommonSuffixOnly) {
    std::string s1 = "123commonsuffix";
    std::string s2 = "456commonsuffix";
    testLCSString(s1, s2, 12, {"commonsuffix"});
}

// Test with multiple common substrings, including special characters and spaces
TEST(SuffixTreeFindLCSStringTest, CommonSubstringWithSpaces) {
    std::string s1 = "Hello World! How are you?";
    std::string s2 = "Hello World! Everyone here?";
    testLCSString(s1, s2, 13, {"Hello World! "});
}



#endif

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}