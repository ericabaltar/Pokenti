#include "Game.h"

Game::Game() {

	loadConfigFile("config.txt");
	initializeMap();

	player.x = player.y = 0;
	player.direction = '>';

}

Game::~Game() {

	cleanupMap();
}

void Game::run() {

	while (true) {

		updateGameLogic();
		drawMap();
		Sleep(100);
	}
}

void Game::loadConfigFile(const std::string& filename) {

	std::ifstream file(filename);

	if (file.is_open()) {

		char separator;
		file >> map.m_width >> separator >> map.m_height >> separator;

	} else {

		std::cerr << "Cannot open configuration file." << std::endl;

	}

	file.close();
}