#include "Tile.h"
#include "../config.h"

Tile::Tile(int p_x, int p_y, Texture2D tex, bool collision) {
	this->dstRect = { 
		static_cast<float>(p_x), 
		static_cast<float>(p_y),
		RENDERED_TILE_SIZE, 
		RENDERED_TILE_SIZE
	};
	this->srcRect = { 0, 0, BASE_TILE_SIZE, BASE_TILE_SIZE };
	this->texture = tex;
	this->is_collide_with_player = collision;
}

void Tile::draw() const {
	DrawTexturePro(this->texture, this->srcRect, this->dstRect, { 0, 0 }, 0, RAYWHITE);
}
