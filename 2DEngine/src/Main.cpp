#include "SDL.h"
#include "Game.h"
#undef main

Game* game = nullptr;

int main() {
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	
	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->Init("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);
	while (game->Running()) {
		frameStart = SDL_GetTicks();

		game->HandleEvents();
		game->Update();
		game->Render();

		frameTime = SDL_GetTicks() - frameStart;

		/* Cap framerate to FPS */
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->Clean();
	return 0;
}

