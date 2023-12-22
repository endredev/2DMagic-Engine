#pragma once

class Map {
public:
	Map();
	~Map();
	void static LoadMap(const char* path, int sizeX, int sizeY);
};

