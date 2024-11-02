#include <gtest/gtest.h>

// Add your test cases here
TEST(SampleTest, AssertionTrue) {
    ASSERT_TRUE(true);
}

// This is where the test suite runs
int main(int argc, char **argv) {
    std::cout << "Hello, World!\n";
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
