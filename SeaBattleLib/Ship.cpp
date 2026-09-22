#include "Ship.h"

Ship::Ship(int size): size(size), hits(0), start(Position(0, 0)), dir(Direction::UNKNOWN) {}

Ship::Ship(int size, Position start, Direction dir) : size(size), hits(0), start(start), dir(dir) {}

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

void Ship::setPositions(const Position& start, const Direction& dir)
{
	this->start = start;
	this->dir = dir;
}
