#include <gtest/gtest.h>

/// TODO Maybe add a script that initializes a brand new docker container and runs the tests in that container

// This is where the test suite runs
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
