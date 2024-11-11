#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

class Player {
private:
	Rectangle srcRect;
	Rectangle dstRect;
	Rectangle collisionDetector;

	Texture2D texture;

	bool isCollided;

	enum CollisionDirection {
		Left = 0,
		Right
	};

	enum State {
		sWalkLeft = 0,
		sWalkRight,
		sIdle
	};

	State currentState;
	CollisionDirection collisionDirection;

	void handle_controls();
	void handle_movement();

	float speed;
public:
	Player(float p_x, float p_y, Texture2D p_texture);
	void update();
	void draw() const;

	Vector2 getPosition();
	Rectangle getDstRect() const;
	Rectangle getCollisionChecker() const;
};

#endif // !Player