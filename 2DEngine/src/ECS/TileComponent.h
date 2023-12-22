#pragma once	
#include "ECS.h"
#include "SDL.h"

class TileComponent : public Component {
public:
	SDL_Texture* texture;
	SDL_Rect srcRect;
	SDL_Rect destRect;
	Vector2D position;
	TileComponent() = default;

	~TileComponent() {
		SDL_DestroyTexture(texture);
	}

	TileComponent(int srcX, int srcY, int xPos, int yPos, const char* path) {
		texture = TextureManager::LoadTexture(path);

		position.x = xPos;
		position.y = yPos;

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = 32;
		srcRect.h = 32;

		destRect.x = xPos;
		destRect.y = yPos;
		destRect.w = 64;
		destRect.h = 64;
	};

	void Update() override {
		/* Where it is vs where do we render it */
		destRect.x = position.x - Game::camera.x;
		destRect.y = position.y - Game::camera.y;
	}

	void Draw() override {
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};