#include "Ship.h"

Ship::Ship(int size): size(size), hits(0), start(Position(0, 0)), dir(Direction::UNKNOWN) {
	if (size < 1 || size>4) {
		throw std::logic_error("Неверный размер корабля");
	}
}

Ship::Ship(int size, Position start, Direction dir) : Ship(size) {
	setup(start, dir);
}

bool Ship::hit(const Position& p)
{
	if (dir == Direction::VERTICAL) {
		for (int i = 0;i < size;i++) {
			if (p.x == start.x && p.y == start.y + i) {
				hits++;
				break;
			}
		}
	}
	else if (dir == Direction::HORIZONTAL) {
		for (int i = 0;i < size;i++) {
			if (p.x == start.x + i && p.y == start.y) {
				hits++;
				break;
			}
		}
	}
	else {
		throw std::logic_error("Неопознанная ориентация корабля");
	}
	return isSunk();
}

void Ship::setup(const Position& start, const Direction& dir)
{
	if (dir == Direction::UNKNOWN) {
		throw std::logic_error("Неопознанная ориентация корабля");
	}
	if (!start.isValid()) {
		throw std::logic_error("Неверная позиция корабля");
	}
	this->start = start;
	this->dir = dir;
}
