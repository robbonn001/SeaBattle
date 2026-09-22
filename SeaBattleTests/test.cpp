#include "pch.h"
#include "Position.h"

TEST(TestPosition, TestIsValid) {
  Position pos(5, 5);
  EXPECT_TRUE(pos.isValid());
}

TEST(TestPosition, TestIsInvalid) {
  Position pos(-1, 5);
  EXPECT_FALSE(pos.isValid());
}

TEST(TestPosition, TestConstructor) {
	Position pos(4, 5);
	EXPECT_EQ(pos.x, 4);
	EXPECT_EQ(pos.y, 5);
}