#pragma once
#include "SDL.h"
#include <stdio.h>
#include <vector>

class ColliderComponent;

class Game {
public:
	Game();
	~Game();

	void Init(const char* title, int xpos, int ypos, int width, int height, bool fullScreen);
	void HandleEvents();
	void Update();
	void Render();
	void Clean();
	bool Running();

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static SDL_Rect camera;
	static std::vector<ColliderComponent*> colliders;
	static void AddTile(int srcX, int srcY, int xPos, int yPos);
	static bool isRunning;
private:
	SDL_Window *window;
};