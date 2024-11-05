#ifndef TILE_H
#define TILE_H

#include <raylib.h>
#include <iostream>

class Tile {
protected:
	Texture2D texture;
	Rectangle srcRect;
	Rectangle dstRect;
	bool is_collide_with_player;
public:
	Tile(int p_x, int p_y, Texture2D tex, bool collision);

	void draw() const;
};

#endif // !TILE_H