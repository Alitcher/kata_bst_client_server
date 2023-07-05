cmake_minimum_required(VERSION 3.12)

# Set the project name and version
project(BSTTest)

# Find the GTest package
find_package(GTest REQUIRED)

# Add the executable for the tests
add_executable(BSTTest BSTTest.cpp ../src/BST.cpp ../src/ServerModel.cpp ../src/Node.cpp)

# Specify the include directories
target_include_directories(BSTTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Link the GTest library
target_link_libraries(BSTTest GTest::GTest GTest::Main)

# Set the C++ standard to C++11
set_property(TARGET BSTTest PROPERTY CXX_STANDARD 11)
