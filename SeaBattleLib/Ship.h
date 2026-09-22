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
	void setup(const Position& start, const Direction& dir);
	int getSize() const {
		return size;
	}
	int getHits() const {
		return hits;
	}
	bool isSunk() const {
		return hits == size; 
	}
	Position getStart() const {
		return start;
	}
	Direction getDirection() const {
		return dir;
	}
private:
	int size;
	int hits;
	Position start;
	Direction dir;
};

