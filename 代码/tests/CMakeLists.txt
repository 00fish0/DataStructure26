cmake_minimum_required(VERSION 3.10)
project(MyProjectTests)

# Find required packages
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

enable_testing()

# Add executable with test source files
add_executable(MyTests 
    test_main.cpp
    # Add other test files here as needed
    # test_LinkedList.cpp
    test_Search.cpp
    ../Search.cpp
)

# Link against Google Test and threading libraries
target_link_libraries(MyTests 
    PRIVATE 
    GTest::gtest 
    GTest::gtest_main
    Threads::Threads
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/..   # 添加上一层目录
)

# Include directories for your source files
target_include_directories(MyTests PRIVATE ${CMAKE_SOURCE_DIR})

# Add test
add_test(NAME MyTests COMMAND MyTests)