#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

class Player {
private:
	Rectangle srcRect;
	Rectangle dstRect;
	Texture2D texture;

	enum State {
		sWalkLeft = 0,
		sWalkRight,
		sIdle
	};

	State currentState;

	void handle_controls();
	void handle_movement();

	float speed;

public:
	Player(float p_x, float p_y, Texture2D p_texture);
	void update();
	void draw() const;

	Vector2 getPosition();
	Rectangle getDstRect() const;
};

#endif // !Player