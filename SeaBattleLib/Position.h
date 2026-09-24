#pragma once

class Position
{
public:
	int x, y;
	Position(int x = 0, int y = 0) : x(x), y(y) {}
	bool operator == (const Position & other) const noexcept {
		return x == other.x && y == other.y;
	}
	bool isValid() const noexcept {
		return x >= 0 && x < 10 && y >= 0 && y < 10;
	}
};

 