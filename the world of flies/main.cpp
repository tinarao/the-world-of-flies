#include <raylib.h>
#include <iostream>
#include "classes/TextureManager.h"
#include "classes/Player.h"

const int SCREEN_H = 1200;
const int SCREEN_W = 600;

int main() {
	InitWindow(SCREEN_H, SCREEN_W, "The World Of Flies");
	SetTargetFPS(60);

	Texture2D tex = TextureManager::GetInstance()->load("assets/player/walk.png", "player_idle");
	Player player = Player(192, 192, tex);

	std::cout << tex.width << std::endl;

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(WHITE);

		player.draw();

		EndDrawing();
	}
	CloseWindow();

	return 0;
}