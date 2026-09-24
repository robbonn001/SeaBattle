#include "GameField.h"

void GameField::show(bool own) const
{
	char c;
	for (int i = 0;i < 10;i++) {
		std::cout << " " << i + 1;
	}
	std::cout << '\n';
	for (int i = 0; i < 10; i++) {
		std::cout << static_cast<char>('a' + i) << " ";
		for (int j = 0; j < 10; j++) {
			switch (grid[i][j]) {
			case static_cast<int>(CellState::EMPTY):
				c = '.'; // пустая клетка
				break;
			case static_cast<int>(CellState::MISS):
				c = 'O'; // промах
				break;
			case static_cast<int>(CellState::HIT):
				c = '*'; // попадание
				break;
			default:
				c = own ? '+' : '.'; // корабль или пустая клетка
			}
			std::cout << c << " ";
		}
		std::cout << '\n';
	}
}

bool GameField::canPlaceShip(const Ship& ship) const
{
	int size = ship.getSize();
	Ship::Direction dir = ship.getDirection();
	Position start = ship.getStart();
	Position cur = start;
	if (dir == Ship::Direction::HORIZONTAL) {
		for (int i = 0;i < size;++i) {
			if (!cur.isValid() || grid[cur.y][cur.x] != 0) {
				return false; // проверка для клеток корабля
			}
			++cur.x;
		}
		// проверка для клеток вокруг корабля
		cur = start;
		--cur.x;
		--cur.y;
		for (int i = 0;i < size + 2;++i) {
			if (cur.isValid() && grid[cur.y][cur.x] != 0) {
				return false;
			}
			++cur.x;
		}
		--cur.x;
		++cur.y;
		if (cur.isValid() && grid[cur.y][cur.x] != 0) {
			return false;
		}
		++cur.y;
		for (int i = 0;i < size + 2;++i) {
			if (cur.isValid() && grid[cur.y][cur.x] != 0) {
				return false;
			}
			--cur.x;
		}
		++cur.x;
		--cur.y;
		if (cur.isValid() && grid[cur.y][cur.x] != 0) {
			return false;
		}
	}
	else if (dir == Ship::Direction::VERTICAL) {
		for (int i = 0;i < size;++i) {
			if (!cur.isValid() || grid[cur.y][cur.x] != 0) {
				return false; // проверка для клеток корабля
			}
			++cur.y;
		}
		// проверка для клеток вокруг корабля
		cur = start;
		++cur.x;
		--cur.y;
		for (int i = 0;i < size + 2;++i) {
			if (cur.isValid() && grid[cur.y][cur.x] != 0) {
				return false;
			}
			++cur.y;
		}
		--cur.y;
		--cur.x;
		if (cur.isValid() && grid[cur.y][cur.x] != 0) {
			return false;
		}
		--cur.x;
		for (int i = 0;i < size + 2;++i) {
			if (cur.isValid() && grid[cur.y][cur.x] != 0) {
				return false;
			}
			--cur.y;
		}
		++cur.y;
		++cur.x;
		if (cur.isValid() && grid[cur.y][cur.x] != 0) {
			return false;
		}
	}
	else {
		throw std::logic_error("Неопознанная ориентация корабля");
	}
	return true;
}

void GameField::placeShip(int id, const Ship& ship)
{
	int size = ship.getSize();
	Ship::Direction dir = ship.getDirection();
	Position start = ship.getStart();
	int* iter = nullptr;
	if (dir == Ship::Direction::HORIZONTAL) {
		iter = &start.x;
	}
	else if (dir == Ship::Direction::VERTICAL) {
		iter = &start.y;
	}
	else {
		throw std::logic_error("Неопознанная ориентация корабля");
	}
	for (int i = 0;i < size;++i) {
		grid[start.y][start.x] = id;
		++(*iter);
	}
}

int GameField::shoot(const Position& pos)
{
	int val = grid[pos.y][pos.x];
	switch (val) {
	case 0:
		grid[pos.y][pos.x] = 11; // промах
		break;
	case 11:
		break; // уже был промах
	case 12:
		break; // уже было попадание
	default:
		grid[pos.y][pos.x] = 12; // попадание
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
		for (int i = 0;i < size + 2;++i) {
			if (cur.isValid() && grid[cur.y][cur.x] == static_cast<int>(CellState::EMPTY)) {
				grid[cur.y][cur.x] = static_cast<int>(CellState::MISS); // помечаем как промах вокруг потопленного корабля
			}
			++cur.x;
		}
		--cur.x;
		++cur.y;
		if (cur.isValid() && grid[cur.y][cur.x] == static_cast<int>(CellState::EMPTY)) {
			grid[cur.y][cur.x] = static_cast<int>(CellState::MISS); // помечаем как промах вокруг потопленного корабля
		}
		++cur.y;
		for (int i = 0;i < size + 2;++i) {
			if (cur.isValid() && grid[cur.y][cur.x] == static_cast<int>(CellState::EMPTY)) {
				grid[cur.y][cur.x] = static_cast<int>(CellState::MISS); // помечаем как промах вокруг потопленного корабля
			}
			--cur.x;
		}
		++cur.x;
		--cur.y;
		if (cur.isValid() && grid[cur.y][cur.x] == static_cast<int>(CellState::EMPTY)) {
			grid[cur.y][cur.x] = static_cast<int>(CellState::MISS); // помечаем как промах вокруг потопленного корабля
		}
	}
	else if (dir == Ship::Direction::VERTICAL) {
		++cur.x;
		--cur.y;
		for (int i = 0;i < size + 2;++i) {
			if (cur.isValid() && grid[cur.y][cur.x] == static_cast<int>(CellState::EMPTY)) {
				grid[cur.y][cur.x] = static_cast<int>(CellState::MISS); // помечаем как промах вокруг потопленного корабля
			}
			++cur.y;
		}
		--cur.y;
		--cur.x;
		if (cur.isValid() && grid[cur.y][cur.x] == static_cast<int>(CellState::EMPTY)) {
			grid[cur.y][cur.x] = static_cast<int>(CellState::MISS); // помечаем как промах вокруг потопленного корабля
		}
		--cur.x;
		for (int i = 0;i < size + 2;++i) {
			if (cur.isValid() && grid[cur.y][cur.x] == static_cast<int>(CellState::EMPTY)) {
				grid[cur.y][cur.x] = static_cast<int>(CellState::MISS); // помечаем как промах вокруг потопленного корабля
			}
			--cur.y;
		}
		++cur.y;
		++cur.x;
		if (cur.isValid() && grid[cur.y][cur.x] == static_cast<int>(CellState::EMPTY)) {
			grid[cur.y][cur.x] = static_cast<int>(CellState::MISS); // помечаем как промах вокруг потопленного корабля
		}
	}
	else {
		throw std::logic_error("Неопознанная ориентация корабля");
	}
}