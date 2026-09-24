#include <iostream>
#include <windows.h>
#include "Game.h"

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	Game().start();
	std::cout << "Нажмите любую клавишу для выхода...\n";
	std::cin.get();
}