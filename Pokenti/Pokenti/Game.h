#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>

struct Player {
	int x, y;
	char direction;
};

struct Map {
	int m_width, m_height;
	char** grid;
};

class Game {
public:
	Game();
	~Game();
	void run();
	void movePlayerUp();
	void movePlayerDown();
	void movePlayerLeft();
	void movePlayerRight();

private:
	Player player;
	Map map;

	void loadConfigFile(const std::string& filename);
	void initializeMap();
	void cleanupMap();
	void drawMap();
	void updateGameLogic();
};


