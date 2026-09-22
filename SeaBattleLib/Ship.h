#pragma once
#include "Position.h"
#include <stdexcept>

class Ship
{	
	
public:
	enum class Direction { UNKNOWN, HORIZONTAL, VERTICAL };
	Ship(int size);
	Ship(int size, Position start, Direction dir);
	bool hit(const Position& p);
	void setPositions(const Position& start, const Direction& dir);
	int getSize() {
		return size;
	}
	int getHits() {
		return hits;
	}
	bool isSunk() {
		return hits == size; 
	}
	Position getStart() {
		return start;
	}
	Direction getDirection() {
		return dir;
	}
private:
	int size;
	int hits;
	Position start;
	Direction dir;
};

