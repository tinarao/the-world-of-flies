#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

class Player {
private:
	Rectangle srcRect;
	Rectangle dstRect;

	Rectangle collisionDetectorX;
	Rectangle collisionDetectorY;
	Vector2 directions;

	Texture2D texture;

	bool isCollided;
	bool isOnFloor;
	bool isJumping;

	enum CollisionDirection {
		Left = 0,
		Right,
		None
	};

	enum State {
		sWalkLeft = 0,
		sWalkRight,
		sIdle
	};

	State currentState;
	CollisionDirection collisionDirection;

	void handle_controls();
	void handle_movement(float ticks);
	void handle_gravity();
	void handle_collisions();
	void lock_collision_detectors_positions();

	float speed;
public:
	Player(float p_x, float p_y, Texture2D p_texture);
	void update();
	void draw() const;

	Vector2 getPosition() const;
	Rectangle getDstRect() const;

	Rectangle getCollisionCheckerX() const;
	Rectangle getCollisionCheckerY() const;
};

#endif // !Player