#pragma once
#include "PG2Graphics.h"
#include <SDL_ttf.h>
#include <vector>

enum MatchingCard
{
	//Chicken, Creeper, Skeleton, Steve, Villager, Zombie, Mooshroom, Chest, Grass, CardBack, CardFront, Cursor, LASTCARD
	Chicken, Cat, Skeleton, Human, Witch, Zombie, Cow, Chest, CardBack, CardFront, Cursor, CurrentPlayer, LASTCARD
};


class Number
{
public:
	Number(SDL_Texture* texture, int width, int height) : texture_(texture), width_(width), height_(height) {}
	~Number()
	{
		//free();
	}
	void free();

	SDL_Texture* Texture() const { return texture_; }
	int Width() const { return width_; }
	int Height() const { return height_; }

private:
	//Image dimensions
	int width_;
	int height_;
	SDL_Texture* texture_;

};

enum ScoreTexture
{
	Player1 = 11, Player2, Separator, Winner, Tie
};


class GameTextures
{
public:
	static void Initialize(SDL_Renderer* renderer);
	static void Cleanup();
	static void RenderNumber(int number, int x, int y, int cellSize, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	static void ScoreItemSize(int number, int& width, int& height);
	static void RenderImage(MatchingCard number, int x, int y, int cellSize, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
private:
	static bool loadRenderedText();
	static void loadImageTextures();
	static void free();

	static SDL_Renderer* renderer_;
	static TTF_Font* font_;

	static int markedIndex_;

	//The actual hardware texture
	static std::vector<Number> scoreTextures_;
	static std::vector<PG2Texture*> imageTextures_;
};

