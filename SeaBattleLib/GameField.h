#pragma once
#include "Ship.h"

class GameField
{
public:
	GameField();
	void show();
    bool placeShip(const Ship& ship);
    int shoot(const Position& pos);
	void shipDie(const Ship& ship);
private:
    int grid[10][10];
};

// 0-9 - индексы кораблей
// 10 - пустая клетка
// 11 - промах
// 12 - попадание