#ifndef MAP_H
#define MAP_H

#include <mutex>
#include <vector>
#include <tinyxml2.h>
#include "../types.h"
#include "Player.h"
#include "Tile.h"

using namespace tinyxml2;

class Map {
private:
	static Map* instance;
	static std::mutex mutex_;

	Map();

	TileMap tilemap;
	std::vector<Tile> tiles;
	int map_w;
	int map_h;

	void parse_tmx();
	Texture2D tileset;
public:
	Map(Map& other) = delete;
	void operator=(const Map&) = delete;
	static Map* GetInstance();

	void draw();
	void load_tiles();
	
	Rectangle GetCollisionRectangleX(Player* player);
	Rectangle GetCollisionRectangleY(Player* player);
};

#endif // !MAP_H