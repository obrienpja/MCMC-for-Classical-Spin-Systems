//
// Created by solidangle on 11/21/19.
//

#include <gtest/gtest.h>

TEST(BasicTest, BasicTest){
    EXPECT_EQ(1, 1);
}

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}