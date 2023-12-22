#include "Map.h"
#include "Game.h"
#include <fstream>

Map::~Map() {

}

Map::Map() {

};

void Map::LoadMap(const char* path, int sizeX, int sizeY) {
	char tile;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX;
	int srcY;

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {

			mapFile.get(tile);
			srcY = atoi(&tile)* 32;

			mapFile.get(tile);
			srcX = atoi(&tile) * 32;

			Game::AddTile(srcX, srcY, x * 64, y * 64);
			mapFile.ignore(); // it's a comma
		}
	}


	mapFile.close();
};