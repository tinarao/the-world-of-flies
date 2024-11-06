#ifndef MAP_H
#define MAP_H

#include <mutex>
#include <tinyxml2.h>
#include "../types.h"

class Map {
private:
	static Map* instance;
	static std::mutex mutex_;

	Map();

	TileMap tilemap;
	int map_w;
	int map_h;

	void parse_tmx();
	void draw();
public:
	Map(Map& other) = delete;
	void operator=(const Map&) = delete;
	static Map* GetInstance();

	void init();
};

#endif // !MAP_H