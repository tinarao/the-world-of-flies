#include "Tile.h"
#include "../config.h"

Tile::Tile(Rectangle p_src, Rectangle p_dst, Texture2D tex, bool collision) {
	this->dstRect = p_dst;
	this->srcRect = p_src;
	this->texture = tex;
	this->is_collide_with_player = collision;
}

void Tile::draw() const {
	DrawTexturePro(this->texture, this->srcRect, this->dstRect, { 0, 0 }, 0, RAYWHITE);
}
