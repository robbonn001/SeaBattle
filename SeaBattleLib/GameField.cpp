#include "GameField.h"

void GameField::show(bool own)
{
	char c;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			switch (grid[i][j]) {
			case 0:
				c = ' '; // пустая клетка
				break;
			case 11:
				c = 'O'; // промах
				break;
			case 12:
				c = '*'; // попадание
				break;
			default:
				c = own ? '+' : ' '; // корабль
			}
			std::cout << c << " ";
		}
		std::cout << std::endl;
	}
}

bool GameField::canPlaceShip(const Ship& ship, const Position& start, const Ship::Direction& dir)
{
	int size = ship.getSize();
	Position cur = start;
	if (dir == Ship::Direction::HORIZONTAL) {
		for (int i = 0;i < size;++i) {
			cur.x += i;
			if ((!cur.isValid() || grid[cur.x][cur.y] != 0) || (cur.y > 0 && grid[cur.x][cur.y - 1] != 0) || (cur.y < 9 && grid[cur.x][cur.y + 1] != 0)) {
				return false;
			}
		}
		++cur.x;
		if ((cur.isValid() && grid[cur.x][cur.y] != 0) || (cur.y > 0 && grid[cur.x][cur.y - 1] != 0) || (cur.y < 9 && grid[cur.x][cur.y + 1] != 0)) {
			return false;
		}
		cur = start;
		--cur.x;
		if ((cur.isValid() && grid[cur.x][cur.y] != 0) || (cur.y > 0 && grid[cur.x][cur.y - 1] != 0) || (cur.y < 9 && grid[cur.x][cur.y + 1] != 0)) {
			return false;
		}
	}
	else if (dir == Ship::Direction::VERTICAL) {
		for (int i = 0;i < size;i++) {
			cur.y += i;
			if ((!cur.isValid() || grid[cur.x][cur.y] != 0) || (cur.x > 0 && grid[cur.x - 1][cur.y] != 0) || (cur.x < 9 && grid[cur.x + 1][cur.y] != 0)) {
				return false;
			}
		}
		++cur.y;
		if ((cur.isValid() && grid[cur.x][cur.y] != 0) || (cur.y > 0 && grid[cur.x - 1][cur.y] != 0) || (cur.y < 9 && grid[cur.x + 1][cur.y] != 0)) {
			return false;
		}
		cur = start;
		--cur.y;
		if ((cur.isValid() && grid[cur.x][cur.y] != 0) || (cur.y > 0 && grid[cur.x - 1][cur.y] != 0) || (cur.y < 9 && grid[cur.x + 1][cur.y] != 0)) {
			return false;
		}
	}
	else {
		throw std::logic_error("Неопознанная ориентация корабля");
	}
	return true;
}

int GameField::shoot(const Position& pos)
{
	int val = grid[pos.x][pos.y];
	switch (val) {
	case 0:
		grid[pos.x][pos.y] = 11; // промах
		break;
	case 11:
		break; // уже был промах
	case 12:
		break; // уже было попадание
	default:
		grid[pos.x][pos.y] = 12; // попадание
	}
	return val; // возвращаем значение клетки до выстрела(индекс корабля или другое)
}

void GameField::shipDie(const Ship& ship)
{
	int size = ship.getSize();
	Position cur = ship.getStart();
	Ship::Direction dir = ship.getDirection();
	if (dir == Ship::Direction::HORIZONTAL) {
		--cur.x;
		--cur.y;
		for (int j = 0;j < 3;++j) {
			cur.y += j;
			for (int i = 0;i < size + 2;++i) {
				cur.x += i;
				if (cur.isValid()) {
					grid[cur.x][cur.y] = 12; // помечаем как подбитую
				}
			}
		}
	}
}
