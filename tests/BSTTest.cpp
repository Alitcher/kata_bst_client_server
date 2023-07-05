#include <gtest/gtest.h>
#include "BST.h"
#include "ServerModel.h"
// #include "ClientModel.h"

// Define test cases for BST
TEST(BSTTest, Insert)
{
    BST bst;
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);

    // Perform assertions to check if the insertions were successful
    ASSERT_TRUE(bst.find(5));
    ASSERT_TRUE(bst.find(3));
    ASSERT_TRUE(bst.find(7));
}

TEST(BSTTest, Remove)
{
    BST bst;
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.remove(3);

    // Perform assertions to check if the removal was successful
    ASSERT_FALSE(bst.find(3));
    ASSERT_TRUE(bst.find(5));
    ASSERT_TRUE(bst.find(7));
}

// // Define test cases for ServerModel
// TEST(ServerModelTest, Start)
// {
//     // Test code for ServerModel
//     // ...
// }

// TEST(ServerModelTest, Run)
// {
//     // Test code for ServerModel
//     // ...
// }

// // Define test cases for ClientModel
// TEST(ClientModelTest, Connect)
// {
//     // Test code for ClientModel
//     // ...
// }

// // TEST(ClientModelTest, HandleUserInput)
// // {
// //     // Test code for ClientModel
// //     // ...
// // }

// Entry point for the tests
int main(int argc, char** argv)
{
    // Initialize the Google Test framework
    ::testing::InitGoogleTest(&argc, argv);

    // Run the tests
    return RUN_ALL_TESTS();
}
