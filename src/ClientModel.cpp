#include <gtest/gtest.h>
#include "BST.h"

// Define test cases using the TEST macro
TEST(BSTTest, Insert)
{
    BST bst;
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);

    // Use assertions to verify the expected behavior
    EXPECT_TRUE(bst.find(5));
    EXPECT_TRUE(bst.find(3));
    EXPECT_TRUE(bst.find(7));
    EXPECT_FALSE(bst.find(10));
}

TEST(BSTTest, Remove)
{
    BST bst;
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);

    bst.remove(3);

    EXPECT_FALSE(bst.find(3));
    EXPECT_TRUE(bst.find(5));
    EXPECT_TRUE(bst.find(7));
}

// ... add more test cases as needed

// Entry point for the tests
int main(int argc, char** argv)
{
    // Initialize the Google Test framework
    ::testing::InitGoogleTest(&argc, argv);

    // Run the tests
    return RUN_ALL_TESTS();
}
