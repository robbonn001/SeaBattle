#include "Position.h"

bool Position::isValid() const
{
	return x >= 0 && x < 10 && y >= 0 && y < 10;
}