#pragma once
#include "Player.h"
#include <ctime>   // для time()

class Game
{
	Player player1, player2;
public:
	Game();
	void start();
	void win(const Player& winner) const noexcept;
};

