#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include <iostream>

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Map* map;
Manager manager;

std::vector<ColliderComponent*> Game::colliders;

enum groupLabels : std::size_t {
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

auto& player(manager.addEntity());
auto& wall(manager.addEntity());
auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

const char* mapFile = "assets/terrain_ss.png";

Game::Game() {};
Game::~Game() {};

bool Game::isRunning = false;
SDL_Rect Game::camera = { 0, 0, 800, 640};

void Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullScreen) {
	/* Set flags for full screen */
	int flags = 0;
	if (fullScreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	/* if sdl subsystems are initialised successfuly */
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems initialised..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			std::cout << "Window created..." << std::endl;

			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer) {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				std::cout << "Renderer created..." << std::endl;
				isRunning = true;

				map = new Map();
				Map::LoadMap("assets/map.map", 25, 25);

				player.addComponent<TransformComponent>(2);
				player.addComponent<SpriteComponent>("assets/player_anim.png", true);
				player.addComponent<KeyboardController>();
				player.addComponent<ColliderComponent>("player");
				player.addGroup(groupPlayers);
			}
		}
	}
	else {
		isRunning = false;
	}
};

void Game::HandleEvents() {
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
};

void Game::Update() {
	manager.Refresh();
	manager.Update();

	camera.x = player.getComponent<TransformComponent>().position.x - 400;
	camera.y = player.getComponent<TransformComponent>().position.y - 320;

	if (camera.x < 0) {
		camera.x = 0;
	}

	if (camera.y < 0) {
		camera.y = 0;
	}

	if (camera.x > camera.w) {
		camera.x = camera.w;
	}

	if (camera.y > camera.h) {
		camera.y = camera.h;
	}
};

void Game::AddTile(int srcX, int srcY, int xPos, int yPos) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xPos, yPos, mapFile);
	tile.addGroup(groupMap);
}

void Game::Render() {
	SDL_RenderClear(renderer);
	
	for (auto& t : tiles) {
		t->Draw();
	}

	for (auto& p : players) {
		p->Draw();
	}


	for (auto& e : enemies) {
		e->Draw();
	}


	SDL_RenderPresent(renderer);
};

void Game::Clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "Game cleared" << std::endl;
};

bool Game::Running() { return isRunning; };