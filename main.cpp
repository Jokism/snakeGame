#include "snakegame.h"
#include <Windows.h>
#include <iostream>

int main() {
	snakegame app = snakegame();

	while (!app.getGameOver()) {
		app.draw();
		app.logic();
		app.input();
		Sleep(15);
	}

	std::cin.get();

	return 0;
}