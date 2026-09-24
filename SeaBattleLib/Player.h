#pragma once
#include <iostream>
#include "GameField.h"
#include "Ship.h"
#include <cstdlib> // для rand()
#include <string>

class Player
{
	int count;
	std::string name;
	GameField field;
	Ship ships[10];
public:
	Player(const std::string& playerName);
	void inputShips();
	void randomShips();
	void showField(bool own = false) const {
		field.show(own);
	}
	int getCellState(const Position& pos) const {
		return field.getCellState(pos);
	}
	bool shootAt(const Position& pos);
	void shipDie(const Ship& ship) {
		field.shipDie(ship);
	}
	bool humanStep(Player& opponent);
	bool botStep(Player& opponent);
	bool isDefeated() const noexcept {
		return count == 0;
	}
	int getShipsCount() const noexcept {
		return count;
	}
	const std::string& getName() const noexcept {
		return name;
	}
};

