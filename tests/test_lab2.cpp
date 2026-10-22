#include <gtest/gtest.h>
#include <sstream>
#include "custom_string.h"

TEST(StringTest, DefaultConstructor) {
    String s;
    EXPECT_EQ(s.size(), 0);
    EXPECT_GE(s.capacity(), 1);
    EXPECT_STREQ(s.str(), "");
}

TEST(StringTest, CStringConstructor) {
    String s("Hello");
    EXPECT_EQ(s.size(), 5);
    EXPECT_GE(s.capacity(), 5);
    EXPECT_STREQ(s.str(), "Hello");
}

TEST(StringTest, CStringConstructorEmpty) {
    String s("");
    EXPECT_EQ(s.size(), 0);
    EXPECT_GE(s.capacity(), 1);
    EXPECT_STREQ(s.str(), "");
}

TEST(StringTest, CopyConstructorDeepCopy) {
    String s1("Test");
    String s2(s1);
    
    EXPECT_STREQ(s1.str(), s2.str());
    s1.append("123");
    EXPECT_STREQ(s2.str(), "Test"); 
}

TEST(StringTest, MoveConstructor) {
    String s1("MoveMe");
    
    String s2(std::move(s1));
    
    EXPECT_STREQ(s2.str(), "MoveMe");
    EXPECT_EQ(s1.size(), 0);          
    EXPECT_EQ(s1.str(), nullptr);
}

TEST(StringTest, CopyAssignmentAndSelfAssignment) {
    String s1("Original");
    String s2("Target");
    s2 = s1;
    EXPECT_STREQ(s2.str(), "Original");
    s1 = s1;
    EXPECT_STREQ(s1.str(), "Original");
    EXPECT_EQ(s1.size(), 8);
}

TEST(StringTest, MoveAssignment) {
    String s1("MoveAssign");
    String s2;
    
    s2 = std::move(s1);
    
    EXPECT_STREQ(s2.str(), "MoveAssign");
    EXPECT_EQ(s1.size(), 0);
    EXPECT_EQ(s1.str(), nullptr);
}

TEST(StringTest, AppendAndCapacityGrowth) {
    String s;
    size_t initial_cap = s.capacity();
    
    s.append("A");
    s.append("B");
    s.append("CDE");
    
    EXPECT_GE(s.capacity(), initial_cap * 2);
    EXPECT_STREQ(s.str(), "ABCDE");
    EXPECT_EQ(s.size(), 5);
}

TEST(StringTest, FindMethod) {
    String s("Hello, World!");
    
    EXPECT_EQ(s.find("World"), 7);
    EXPECT_EQ(s.find("Hello"), 0);
    EXPECT_EQ(s.find("xyz"), String::npos); 
    EXPECT_EQ(s.find(""), 0);               
}

TEST(StringTest, WrapPdfExample) {
    String s("aa bb ccc");
    String res = s.wrap(4);
    EXPECT_STREQ(res.str(), "aa\nbb\nccc");
}

TEST(StringTest, WrapLongWordNoBreak) {
    String s("abcde f");
    String res = s.wrap(3);
    EXPECT_STREQ(res.str(), "abcde\nf");
}

TEST(StringTest, WrapMultipleSpaces) {
    String s("a  b b c c");
    String res = s.wrap(4);
    EXPECT_STREQ(res.str(), "a  b\nb c\nc");
}

TEST(StringTest, WrapEdgeCases) {
    String s1("");
    EXPECT_STREQ(s1.wrap(5).str(), "");
    String s2("hello");
    EXPECT_STREQ(s2.wrap(0).str(), "");
    String s3("hi");
    EXPECT_STREQ(s3.wrap(10).str(), "hi");
}