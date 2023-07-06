cmake_minimum_required(VERSION 3.12)
project(BSTTest)

message("GTEST_LIB_DIR: $ENV{GTEST_LIB_DIR}")
message("GTEST_INCLUDE_DIR: $ENV{GTEST_INCLUDE_DIR}")

# Add the executable for the tests
add_executable(BSTTest BSTTest.cpp ../src/BST.cpp ../src/ServerModel.cpp ../src/Node.cpp)



# Check if the platform is Windows
if(WIN32)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(GTEST_LIB_DIR $ENV{GTEST_LIB_DIR}) # => set(GTEST_LIB_DIR "C:/Libraries/gtest/googletest/build/lib/Debug")

    target_link_libraries(BSTTest
        ${GTEST_LIB_DIR}/gmock.lib
        ${GTEST_LIB_DIR}/gmock_main.lib
        ${GTEST_LIB_DIR}/gtest.lib
        ${GTEST_LIB_DIR}/gtest_main.lib
    )

    target_include_directories(BSTTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include $ENV{GTEST_INCLUDE_DIR}) =>  "C:/Libraries/gtest/googletest/googletest/include")

elseif(UNIX AND NOT APPLE)
    find_package(GTest REQUIRED)
    target_include_directories(BSTTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
    target_link_libraries(BSTTest GTest::GTest GTest::Main)
    
endif()

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
