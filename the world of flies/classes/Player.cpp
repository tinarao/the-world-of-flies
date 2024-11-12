#include <iostream>
#include "Player.h"
#include "../config.h"
#include "Map.h"

#define TRANSPARENT_COLOR { 0, 0, 0, 0 }

Player::Player(float p_x, float p_y, Texture2D p_texture) {
	this->dstRect = { p_x, p_y, RENDERED_TILE_SIZE, RENDERED_TILE_SIZE };
	this->srcRect = { 0, 0, BASE_TILE_SIZE, BASE_TILE_SIZE };
	this->currentState = sIdle;
	this->texture = p_texture;
	this->speed = 150;

	/*this->collisionDetector = { this->dstRect.x + RENDERED_TILE_SIZE / 2, this->dstRect.y + RENDERED_TILE_SIZE / 2, this->dstRect.width / 2 + 1, 8 };*/
	this->collisionDetector = { 
		this->dstRect.x - 1, 
		this->dstRect.y, 
		this->dstRect.width + 2,
		this->dstRect.height
	};
}

void Player::draw() const {
	DrawTexturePro(
		this->texture, 
		this->srcRect, 
		this->dstRect, 
		{ 0, 0 }, 
		0, 
		WHITE
	);

	DrawRectanglePro(this->collisionDetector, { 0,0 }, 0.0f, PINK);
}

Vector2 Player::getPosition() {
	Vector2 pos = { 
		this->dstRect.x, 
		this->dstRect.y
	};

	return pos;
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

	this->collisionDetector.x = this->dstRect.x - 1;
	this->collisionDetector.y = this->dstRect.y + RENDERED_TILE_SIZE / 2;
}

void Player::handle_movement() {
	float tick = GetFrameTime();

	Rectangle collision = Map::GetInstance()->GetCollisionRectangle(this);
	if (collision.width != 0) {
		this->isCollided = true;
		this->collisionDirection = this->dstRect.x - collision.x > 0 ? Left : Right;
	}
	else {
		this->isCollided = false;
	}

	this->handleGravity(tick);
	if (!this->isOnFloor) {
		this->dstRect.y += tick * speed;
	}

	switch (this->currentState) {
	case sWalkLeft:
		if (isCollided && this->collisionDirection == Left) {
			break;
		}

		this->dstRect.x -= this->speed * tick;
		this->srcRect.width = BASE_TILE_SIZE;
		break;
	case sWalkRight:
		if (isCollided && this->collisionDirection == Right) {
			break;
		}

		this->dstRect.x += this->speed * tick;
		this->srcRect.width = -BASE_TILE_SIZE;
		break;
	default:
		break;
	}
}

Rectangle Player::getDstRect() const {
	return this->dstRect;
}

Rectangle Player::getCollisionChecker() const {
	return this->collisionDetector;
}

void Player::handleGravity(float ticks) {
	Rectangle collision = Map::GetInstance()->GetCollisionRectangle(this);
	this->isOnFloor = collision.y == 0;
}
