#include <raylib.h>

const int SCREEN_H = 1200;
const int SCREEN_W = 600;

int main() {
	InitWindow(SCREEN_H, SCREEN_W, "The World Of Flies");

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);

		DrawText("The World Of Flies", 100, 50, 36, RAYWHITE);

		EndDrawing();
	}
	CloseWindow();

	return 0;
}