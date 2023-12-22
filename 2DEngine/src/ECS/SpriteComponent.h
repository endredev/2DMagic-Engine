#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "../Game.h"
#include "Animation.h"
#include <map>


class SpriteComponent : public Component {
public:
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
	std::map<const char*, Animation> animations;

	SpriteComponent() = default;

	SpriteComponent(const char* path) {
		SetTexture(path);
	}

	SpriteComponent(const char* path, bool mIsAnimated) {
		isAnimated = mIsAnimated;

		Animation idle = Animation(0, 3, 100);
		Animation walk = Animation(1, 3, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		Play("Walk");
		SetTexture(path);
	}

	~SpriteComponent() {
		SDL_DestroyTexture(texture);
	}

	void SetTexture(const char* path) {
		texture = TextureManager::LoadTexture(path);
	}

	void Init() override {
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;

		destRect.x = 0;
		destRect.y = 0;
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void Update() override {

		if (isAnimated) {
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void Draw() override {
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}

	void Play(const char* animName) {
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}

private:
	TransformComponent *transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	bool isAnimated = false;
	int animIndex = 0;
	int frames = 0;
	int speed = 100; // delay between frames
};