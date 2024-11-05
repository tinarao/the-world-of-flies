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

public:
	Player(float p_x, float p_y, Texture2D p_texture);
	void draw() const;
};

#endif // !Player