#include "pch.h"
#include "Position.h"
#include "Ship.h"
#include "GameField.h"
#include "Player.h"
#include "Game.h"

// Position tests

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

// Ship tests

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

TEST(ShipHitTest, HitRightPositions) {
	Ship ship1(3, Position(0, 0), Ship::Direction::HORIZONTAL);
	ship1.hit(Position(2, 0));
	EXPECT_EQ(ship1.getHits(), 1);
	Ship ship2(3, Position(0, 0), Ship::Direction::VERTICAL);
	ship2.hit(Position(0, 2));
	EXPECT_EQ(ship2.getHits(), 1);
}

TEST(ShipTest, HitWrongPosition) {
	Position start(0, 0);
	Ship ship(2, start, Ship::Direction::VERTICAL);

	// Бьем мимо корабля
	bool result = ship.hit(Position(5, 5));
	EXPECT_FALSE(result);
	EXPECT_FALSE(ship.isSunk());
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

// GameField tests

TEST(GameFieldTest, PlaceShipHorizontal) {
	GameField field;
	Position start(0, 0);
	Ship ship(2, start, Ship::Direction::HORIZONTAL);

	EXPECT_TRUE(field.canPlaceShip(ship));
	field.placeShip(1, ship);

	// Проверяем, что клетки заняты ID корабля (1)
	EXPECT_EQ(field.getCellState(Position(0, 0)), 1);
	EXPECT_EQ(field.getCellState(Position(1, 0)), 1);
}

TEST(GameFieldTest, PlaceShipOverlap) {
	GameField field;
	Ship ship1(2, Position(0, 0), Ship::Direction::HORIZONTAL);
	field.placeShip(1, ship1);

	Ship ship2(2, Position(0, 0), Ship::Direction::VERTICAL);
	EXPECT_FALSE(field.canPlaceShip(ship2)); // Нельзя ставить поверх другого
}

TEST(GameFieldTest, ShootMiss) {
	GameField field;
	int result = field.shoot(Position(5, 5));

	EXPECT_EQ(result, 0); // Было пусто
	// После выстрела там должен быть промах (11)
	EXPECT_EQ(field.getCellState(Position(5, 5)), 11);
}

TEST(GameFieldTest, ShootHit) {
	GameField field;
	Ship ship(1, Position(2, 2), Ship::Direction::HORIZONTAL);
	field.placeShip(5, ship); // Ставим корабль с ID 5

	int result = field.shoot(Position(2, 2));
	EXPECT_EQ(result, 5); // Вернул ID корабля
	EXPECT_EQ(field.getCellState(Position(2, 2)), 12); // Стало попаданием
}

TEST(GameFieldTest, DoubleShoot) {
	GameField field;
	field.shoot(Position(0, 0)); // Первый выстрел - промах

	int result = field.shoot(Position(0, 0)); // Второй туда же
	EXPECT_EQ(result, 11); // Должен вернуть состояние "уже был промах"
}

// --- Тест для обводки убитого корабля ---
TEST(GameFieldTest, ShipDieSurrounding) {
	GameField field;
	// Ставим однопалубный корабль в центре
	Ship ship(1, Position(5, 5), Ship::Direction::HORIZONTAL);
	field.placeShip(1, ship);

	// Топим его
	field.shoot(Position(5, 5));
	field.shipDie(ship);

	// Проверяем соседей. Они должны стать промахами (11), а не попаданиями (12)
	EXPECT_EQ(field.getCellState(Position(4, 4)), 11);
	EXPECT_EQ(field.getCellState(Position(4, 5)), 11);
	EXPECT_EQ(field.getCellState(Position(4, 6)), 11);
	EXPECT_EQ(field.getCellState(Position(5, 4)), 11);
	EXPECT_EQ(field.getCellState(Position(5, 6)), 11);
	EXPECT_EQ(field.getCellState(Position(6, 4)), 11);
	EXPECT_EQ(field.getCellState(Position(6, 5)), 11);
	EXPECT_EQ(field.getCellState(Position(6, 6)), 11);
}

// Тест расстановки кораблей
TEST(PlayerTest, RandomShipsPlacement) {
	Player p("TestBot");
	EXPECT_EQ(p.getName(), "TestBot");
	p.randomShips();

	// Проверяем, что все корабли расставлены (count должен быть 10)
	EXPECT_EQ(p.getShipsCount(), 10);

	// Проверяем, что на поле есть корабли (значения от 1 до 10)
	bool hasShips = false;
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			if (p.getCellState(Position(i, j)) > 0 && p.getCellState(Position(i, j)) <= 10) {
				hasShips = true;
			}
		}
	}
	EXPECT_TRUE(hasShips);
}