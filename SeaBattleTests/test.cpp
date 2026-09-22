#include "pch.h"
#include "Position.h"
#include "Ship.h"

TEST(PositionIsValidTest, IsValid) {
  Position pos(5, 5);
  EXPECT_TRUE(pos.isValid());
}

TEST(PositionIsValidTest, IsInvalid) {
  Position pos(-1, 5);
  EXPECT_FALSE(pos.isValid());
}

TEST(PositionConstructorTest, ValidArguments) {
	Position pos(4, 5);
	EXPECT_EQ(pos.x, 4);
	EXPECT_EQ(pos.y, 5);
}

TEST(ShipConstructorTest, ValidSize) {
	Ship ship(3);
	EXPECT_EQ(ship.getSize(), 3);
}

TEST(ShipConstructorTest, InvalidSize) {
	EXPECT_THROW(Ship ship(0), std::logic_error);
	EXPECT_THROW(Ship ship(5), std::logic_error);
}

TEST(ShipConstructorTest, ValidArguments) {
	Position pos(4, 5);
	Ship ship(3, pos, Ship::Direction::HORIZONTAL);
	EXPECT_EQ(ship.getSize(), 3);
	EXPECT_EQ(ship.getStart(), pos);
	EXPECT_EQ(ship.getDirection(), Ship::Direction::HORIZONTAL);
}
TEST(ShipConstructorTest, InvalidArguments) {
	EXPECT_THROW(Ship ship(3, Position(-1, 5), Ship::Direction::HORIZONTAL), std::logic_error);
	EXPECT_THROW(Ship ship(3, Position(4, 5), Ship::Direction::UNKNOWN), std::logic_error);
}

TEST(ShipHorizontalHitTest, IncreaseHit) {
	Ship ship(3, Position(0, 0), Ship::Direction::HORIZONTAL);
	ship.hit(Position(2, 0));
	EXPECT_EQ(ship.getHits(), 1);
}

TEST(ShipVerticalHitTest, IncreaseHit) {
	Ship ship(3, Position(0, 0), Ship::Direction::VERTICAL);
	ship.hit(Position(0, 2));
	EXPECT_EQ(ship.getHits(), 1);
}

TEST(ShipHitTest, isSunk) {
	Ship ship(2, Position(0, 0), Ship::Direction::HORIZONTAL);
	ship.hit(Position(0, 0));
	ship.hit(Position(1, 0));
	EXPECT_TRUE(ship.isSunk());
}

TEST(ShipHitTest, LogicError) {
	Ship ship(2);
	EXPECT_THROW(ship.hit(Position(0, 0)), std::logic_error);
}