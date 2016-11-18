include_directories(${gtest_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR})
set(TEST_SOURCES main_test.cpp Vec_test.cpp Seg_test.cpp)
add_executable(engine2d_tests ${TEST_SOURCES})
target_link_libraries(engine2d_tests gtest engine2d_main)