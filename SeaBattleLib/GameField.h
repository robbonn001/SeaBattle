#pragma once
#include <iostream>
#include "Ship.h"

class GameField
{
public:
	GameField();
	void show(bool own = false);
    bool canPlaceShip(const Ship& ship, const Position& start, const Ship::Direction& dir);
    int shoot(const Position& pos);
	void shipDie(const Ship& ship);
private:
	int grid[10][10]{};
};

// 0 - пустая клетка
// 1-10 - индексы кораблей
// 11 - промах
// 12 - попадание