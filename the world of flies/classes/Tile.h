#ifndef TILE_H
#define TILE_H

#include <raylib.h>
#include <iostream>

#define GRASS_TILE 2
#define DIRT_TILE 12

enum TileVariant {
	Air = 0,
	Grass = 2,
	Dirt = 12
};

class Tile {
protected:
	Texture2D texture;
	Rectangle srcRect;
	Rectangle dstRect;
	bool is_collide_with_player;
public:
	Tile(Rectangle p_src, Rectangle p_dst, Texture2D tex, bool collision) {
		this->dstRect = p_dst;
		this->srcRect = p_src;
		this->texture = tex;
		this->is_collide_with_player = collision;
	}

	void draw() const {
		DrawTexturePro(this->texture, this->srcRect, this->dstRect, { 0, 0 }, 0, RAYWHITE);
	}

	Rectangle getDstRect() const {
		return this->dstRect;
	}
};

#endif // !TILE_H