#pragma once
#include <iostream>
#include "Ship.h"

class GameField
{
public:
	void show(bool own = false) const;
    bool canPlaceShip(const Ship& ship) const;
	void placeShip(int id, const Ship& ship);
    int shoot(const Position& pos);
	void shipDie(const Ship& ship);
	int getCellState(const Position& pos) const
	{
		return pos.isValid() ? grid[pos.y][pos.x] : -1;
	}
private:
	int grid[10][10]{};
};

// 0 - пустая клетка (.)
// 1-10 - индексы кораблей (+)
// 11 - промах (0)
// 12 - попадание (*)