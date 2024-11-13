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
	this->speed = 250;
	this->directions = { 0, 0 };
	this->isJumping = false;

	this->isCollided = false;
	this->isOnFloor = false;
	this->collisionDirection = None;

	this->collisionDetectorX = { 
		0, 
		0,
		this->dstRect.width + 2,
		this->dstRect.height - RENDERED_TILE_SIZE / 2
	};

	this->collisionDetectorY = {
		0,
		0,
		this->dstRect.width / 2,
		RENDERED_TILE_SIZE / 2
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

	DrawRectanglePro(this->collisionDetectorX, { 0, 0 }, 0.0f, { 255, 0, 0, 64 });
	DrawRectanglePro(this->collisionDetectorY, { 0, 0 }, 0.0f, { 0, 255, 0, 64 });
}

Vector2 Player::getPosition() const {
	Vector2 pos = { 
		this->dstRect.x, 
		this->dstRect.y
	};

	return pos;
}

void Player::handle_controls() {
	if (IsKeyDown(PLAYER_MOVE_L)) {
		this->currentState = sWalkLeft;
		this->directions.x = -1;
	} else if (IsKeyDown(PLAYER_MOVE_R)) {
		this->currentState = sWalkRight;
		this->directions.x = 1;
	} else if (IsKeyDown(PLAYER_JUMP)) {
		this->isJumping = true;
	} else {
		this->currentState = sIdle;
		this->directions = { 0, 0 };
	}
}

void Player::update() {
	float ticks = GetFrameTime();

	this->handle_controls();
	this->handle_gravity();
	this->handle_collisions();
	this->handle_movement(ticks);
	this->lock_collision_detectors_positions();
}

void Player::lock_collision_detectors_positions() {
	this->collisionDetectorX.x = this->dstRect.x - 1;
	this->collisionDetectorX.y = this->dstRect.y + RENDERED_TILE_SIZE / 8;

	this->collisionDetectorY.x = this->dstRect.x + RENDERED_TILE_SIZE / 4;
	this->collisionDetectorY.y = this->dstRect.y + RENDERED_TILE_SIZE / 2;
}

void Player::handle_collisions() {
	Rectangle collision = Map::GetInstance()->GetCollisionRectangleX(this);
	if (collision.x != 0) {
		this->isCollided = true;
		this->collisionDirection = this->dstRect.x - collision.x > 0 ? Left : Right;
	}
	else {
		this->isCollided = false;
	}
}

void Player::handle_movement(float ticks) {
	bool isMovingLeftIsProhibited = this->isCollided && this->collisionDirection == Left;
	bool isMovingRightIsProhibited = this->isCollided && this->collisionDirection == Right;

	if (!isMovingLeftIsProhibited && this->directions.x < 0) {
		this->dstRect.x += this->directions.x * this->speed * ticks;
	}
	else if (!isMovingRightIsProhibited && this->directions.x > 0) {
		this->dstRect.x += this->directions.x * this->speed * ticks;
	}

	this->dstRect.y += this->directions.y * this->speed * ticks;
}

Rectangle Player::getDstRect() const {
	return this->dstRect;
}

Rectangle Player::getCollisionCheckerX() const {
	return this->collisionDetectorX;
}

Rectangle Player::getCollisionCheckerY() const {
	return this->collisionDetectorY;
}

void Player::handle_gravity() {
	Rectangle collision = Map::GetInstance()->GetCollisionRectangleY(this);

	this->isOnFloor = ((collision.y + static_cast<float>(RENDERED_TILE_SIZE)) - this->dstRect.y) > 2;
	if (!this->isOnFloor) {
		this->directions.y = 1;
	}
}
