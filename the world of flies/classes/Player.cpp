#include "Player.h"

Player::Player(float p_x, float p_y, Texture2D p_texture) {
	this->dstRect = { p_x, p_y, 128, 128 };
	this->srcRect = { 0, 0, 32, 32 };
	this->currentState = sIdle;
	this->texture = p_texture;
}

void Player::draw() const {
	DrawTexturePro(this->texture, this->srcRect, this->dstRect, { 0, 0 }, 0, WHITE);
}