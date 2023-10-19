include_directories(/path/to/googletest/include)
link_directories(/path/to/googletest/lib)

set(TEST_SOURCES
    test_max30102.cpp
)

add_executable(runTests ${TEST_SOURCES})
target_link_libraries(runTests gtest gtest_main pthread)