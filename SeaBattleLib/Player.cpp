#include "Player.h"

Player::Player(const std::string& playerName) : name(playerName), ships{ 4,3,3,2,2,2,1,1,1,1 }, count(0) {}

void Player::inputShips()
{
	int count = 0;
	while(count!=10)
	{
		field.show(true);
		int x, y;
		char c, d, charx, chary;
		std::cout << "Для корабля длины " << ships[count].getSize() << " введите стартовую позицию и направление корабля (например, a 1 h или b 2 v): \n";
		std::cin >> chary >> charx >> d;
		x = charx - '1';
		y = chary - 'a';
		Position start(x, y);
		if (!start.isValid()) {
			std::cout << "Некорректная позиция! Попробуйте снова.\n";
			continue;
		}
		if (d != 'h' && d != 'v') {
			std::cout << "Некорректное направление! Попробуйте снова.\n";
			continue;
		}
		ships[count].setup(start, d == 'h' ? Ship::Direction::HORIZONTAL : Ship::Direction::VERTICAL);
		if (!field.canPlaceShip(ships[count])) {
			std::cout << "Некорректное расположение корабля! Попробуйте снова.\n";
			continue;
		}
		field.placeShip(++count, ships[count]);
	}
	this->count = count;
}

void Player::randomShips()
{
	int count = 0;
	while (count != 10) {
		int x = std::rand() % 10;
		int y = std::rand() % 10;
		Position start(x, y);
		Ship::Direction dir = (std::rand() % 2 == 0) ? Ship::Direction::HORIZONTAL : Ship::Direction::VERTICAL;
		ships[count].setup(start, dir);
		if (!field.canPlaceShip(ships[count])) {
			continue;
		}
		field.placeShip(++count, ships[count]);
	}
	this->count = count;
}

bool Player::botStep(Player& opponent) {
	Position pos;
	bool validShot = false;

	while (!validShot) {
		int x = std::rand() % 10;
		int y = std::rand() % 10;
		pos = Position(x, y);
		// Проверяем, не стреляли ли мы сюда раньше. 
		int state = opponent.getCellState(pos);
		// Стреляем только если клетка пустая (0) или с кораблем (1-10)
		if (state == static_cast<int>(GameField::CellState::EMPTY) || (state > static_cast<int>(GameField::CellState::EMPTY) && state <= 10)) {
			validShot = true;
		}
	}
	return opponent.shootAt(pos); // Делаем выстрел;
}

bool Player::shootAt(const Position& pos)
{
	int id = field.shoot(pos);
	if (id > 0 && id <= 10) {
		std::cout << "Попадание!\n";
		if (ships[id - 1].hit(pos)) {
			std::cout << "Корабль потоплен!\n";
			field.shipDie(ships[id - 1]);
			count--;
		}
		return true;
	}
	std::cout << "Промах!";
	return false;
}

bool Player::humanStep(Player& opponent)
{
	Position pos;
	while (true) {
		std::cout << "\nВаше поле:\n";
		field.show(true);
		std::cout << "\nПоле противника:\n";
		opponent.showField();
		int x, y;
		char c;
		std::cout << "Введите координаты выстрела (например, a 1 или b 2): \n";
		std::cin >> c >> x;
		y = c - 'a';
		pos = Position(x - 1, y);
		if (!pos.isValid()) {
			std::cout << "Некорректная позиция! Попробуйте снова.\n";
			continue;
		}
		if (field.getCellState(pos) > 10) {
			std::cout << "Вы уже сюда били! Попробуйте снова.\n";
			continue;
		}
		break;
	}
	return opponent.shootAt(pos);
}
