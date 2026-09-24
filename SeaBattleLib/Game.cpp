#include "Game.h"

Game::Game() : player1("Игрок"), player2("Бот")
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void Game::start()
{
	std::cout << "Расставьте свои корабли:\n";
	player1.inputShips();
	std::cout << "Бот расставляет корабли...\n";
	player2.randomShips();
	while (true) {
		while (player1.humanStep(player2)) {
			if (player2.isDefeated()) {
				win(player1);
				return;
			}
		}
		while (player2.botStep(player1)) {
			if (player1.isDefeated()) {
				win(player2);
				return;
			}
		}
	}
}

void Game::win(const Player& winner) const noexcept
{
	std::cout << "Победил игрок: " << winner.getName() << " с " << winner.getShipsCount() << " кораблями!\n";
}
