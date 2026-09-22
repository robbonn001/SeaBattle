#pragma once

class Position
{
public:
	int x, y;
	Position(int x = 0, int y = 0) : x(x), y(y) {}
	bool isValid() const noexcept;
};

 