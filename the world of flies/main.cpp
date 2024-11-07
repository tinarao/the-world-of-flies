#include <raylib.h>
#include <iostream>
#include "classes/TextureManager.h"
#include "classes/Player.h"
#include "config.h"
#include "classes/Map.h"

int main() {
	InitWindow(SCREEN_H, SCREEN_W, "The World Of Flies");
	SetTargetFPS(60);

	Texture2D player_tex = TextureManager::GetInstance()->load("assets/player/walk.png", "player_idle");
	Texture2D grass_tex = TextureManager::GetInstance()->load("assets/terrain/grass.png", "terrain_grass");
	Player player = Player(1000, 192, player_tex);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(WHITE);

		player.update();
		Map::GetInstance()->draw();

		EndDrawing();
	}

	TextureManager::GetInstance()->clean();
	CloseWindow();

	return 0;
}