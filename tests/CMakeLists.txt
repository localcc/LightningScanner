include(FetchContent)
include(GoogleTest)

set(gtest_force_shared_crt ON)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.13.0
)
FetchContent_MakeAvailable(googletest)

add_executable(LargePattern "LargePattern.cpp")
target_link_libraries(LargePattern PRIVATE GTest::gtest_main LightningScanner)

add_executable(SmallPattern "SmallPattern.cpp")
target_link_libraries(SmallPattern PRIVATE GTest::gtest_main LightningScanner)

add_executable(SimilarPattern "SimilarPattern.cpp")
target_link_libraries(SimilarPattern PRIVATE GTest::gtest_main LightningScanner)

enable_testing()
gtest_discover_tests(LargePattern)
gtest_discover_tests(SmallPattern)
gtest_discover_tests(SimilarPattern)