cmake_minimum_required(VERSION 3.12)
project(BSTTest)
find_package(GTest REQUIRED)

# Add the executable for the tests
add_executable(BSTTest BSTTest.cpp ../src/BST.cpp ../src/ServerModel.cpp ../src/Node.cpp)

# Specify the include directories
target_include_directories(BSTTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Link the GTest library
target_link_libraries(BSTTest GTest::GTest GTest::Main)

# Set the C++ standard to C++11
set_property(TARGET BSTTest PROPERTY CXX_STANDARD 11)

# Define a custom target for cleaning
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/CMakeCache.txt
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/CMakeFiles/
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/cmake_install.cmake
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/Makefile
    # Add more commands to remove additional files/directories as needed
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Make the clean-all target depend on the all target
add_dependencies(clean-all BSTTest)
