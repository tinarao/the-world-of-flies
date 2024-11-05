#include <iostream>
#include "Player.h"
#include "../config.h"

Player::Player(float p_x, float p_y, Texture2D p_texture) {
	this->dstRect = { p_x, p_y, RENDERED_TILE_SIZE, RENDERED_TILE_SIZE };
	this->srcRect = { 0, 0, BASE_TILE_SIZE, BASE_TILE_SIZE };
	this->currentState = sIdle;
	this->texture = p_texture;
	this->speed = 5;
}

void Player::draw() const {
	DrawTexturePro(this->texture, this->srcRect, this->dstRect, { 0, 0 }, 0, WHITE);
}

void Player::handle_controls() {
	if (IsKeyDown(PLAYER_MOVE_L)) {
		this->currentState = sWalkLeft;
	} else if (IsKeyDown(PLAYER_MOVE_R)) {
		this->currentState = sWalkRight;
	} else {
		this->currentState = sIdle;
	}
}

void Player::update() {
	this->handle_controls();
	this->handle_movement();

	// Call latest
	this->draw();
}

void Player::handle_movement() {
	switch (this->currentState) {
	case sWalkLeft:
		std::cout << "Move Left" << std::endl;
		this->dstRect.x -= this->speed;
		this->srcRect.width = BASE_TILE_SIZE;
		break;
	case sWalkRight:
		std::cout << "Move Right" << std::endl;
		this->dstRect.x += this->speed;
		this->srcRect.width = -BASE_TILE_SIZE;
		break;
	default:
		break;
	}
}