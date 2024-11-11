#include <raylib.h>
#include <iostream>
#include "classes/TextureManager.h"
#include "classes/Player.h"
#include "config.h"
#include "classes/Map.h"

int main() {
	InitWindow(SCREEN_W, SCREEN_H, "The World Of Flies");
	SetTargetFPS(60);

	Texture2D bg_tex = TextureManager::GetInstance()->load("assets/bg.png", "bg");
	Texture2D player_tex = TextureManager::GetInstance()->load("assets/player/walk.png", "player_idle");
	Texture2D grass_tex = TextureManager::GetInstance()->load("assets/terrain/grass.png", "terrain_grass");
	Player player = Player(100, 450, player_tex);

	Camera2D camera = Camera2D{
		{ SCREEN_W / 2 - RENDERED_TILE_SIZE / 2, SCREEN_H / 2 - RENDERED_TILE_SIZE / 2 },
		{ 0, 0 },
		0.0f,
		0.5f
	};

	Map::GetInstance()->load_tiles();

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(WHITE);

		// Update stage
			player.update();
		// End Of Update Stage


		// Draw stage
			BeginMode2D(camera);
			camera.target = player.getPosition();

			// Camera zoom controls
			camera.zoom += ((float)GetMouseWheelMove() * 0.05f);
			if (camera.zoom > 3.0f) camera.zoom = 3.0f;
			else if (camera.zoom < 0.1f) camera.zoom = 0.1f;

			DrawTextureEx(bg_tex, { 0, 0 }, 0, 2, RAYWHITE);
			Map::GetInstance()->draw();
			player.draw();

			EndMode2D();
		// End Of Draw Stage

		EndDrawing();
	}

	TextureManager::GetInstance()->clean();
	CloseWindow();

	return 0;
}