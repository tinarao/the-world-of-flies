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
	Texture2D tileset;
public:
	Map(Map& other) = delete;
	void operator=(const Map&) = delete;
	static Map* GetInstance();

	void draw() const;
};

#endif // !MAP_H