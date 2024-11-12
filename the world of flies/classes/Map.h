#ifndef MAP_H
#define MAP_H

#include <mutex>
#include <vector>
#include <tinyxml2.h>
#include "../types.h"
#include "Player.h"
#include "Tile.h"

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
	Rectangle GetCollisionRectangle(Player* player);
	void load_tiles();
};

#endif // !MAP_H