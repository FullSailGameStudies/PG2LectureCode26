#include "GameTextures.h"

TTF_Font* GameTextures::font_ = NULL;
std::vector<Number> GameTextures::scoreTextures_;
std::vector<PG2Texture*> GameTextures::imageTextures_;
SDL_Renderer* GameTextures::renderer_;
int GameTextures::markedIndex_ = 9;



void GameTextures::Initialize(SDL_Renderer* renderer)
{
	if (font_ == NULL)
	{
		font_ = TTF_OpenFont("consola.ttf", 28);
		if (font_ == NULL)
		{
			printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		}
	}
	renderer_ = renderer;
	loadRenderedText();
	loadImageTextures();
}

void GameTextures::loadImageTextures()
{
	PG2Texture* texture;
	//std::vector<std::string> files{ "chicken.png","creeper.png","skeleton.png","steve.png","villager.png","zombie.png","mooshroom.png","chest.png","grass.jpg" };
	std::vector<std::string> files{ 
		"chickenFace.png","catFace.png","skeletonFace.png","humanFace.png","witchFace.png","zombieFace.png","cowFace.png","chest2.png","cardBack.png", "cardFront.png", "cursor4.png", "currentPlayer.png"
	};
	//std::vector<SDL_BlendMode> modes { SDL_BLENDMODE_BLEND,}
	for (size_t i = 0; i < files.size(); i++)
	{
		texture = new PG2Texture(renderer_);
		if (texture->LoadFromFile(files[i]))
		{
			imageTextures_.push_back(texture);
			texture->BlendMode(SDL_BLENDMODE_BLEND);
			texture->Alpha(255); // Fully opaque
		}

	}
	//imageTextures_[MatchingCard::Cursor]->BlendMode(SDL_BLENDMODE_MUL);
	imageTextures_[MatchingCard::CurrentPlayer]->BlendMode(SDL_BLENDMODE_NONE);
}

void GameTextures::Cleanup()
{
	free();
}

void GameTextures::free()
{
	//Free textures if they exists
	for (auto& number : scoreTextures_)
	{
		number.free();
		//if (texture != NULL)
		//{
		//	SDL_DestroyTexture(texture);
		//	texture = NULL;
		//}
	}
	//width_ = 0;
	//height_ = 0;

	for (auto& imageTex : imageTextures_)
	{
		delete imageTex;
	}
	imageTextures_.clear();

	if (font_ != NULL)
	{
		TTF_CloseFont(font_);
		font_ = NULL;
	}
}

bool GameTextures::loadRenderedText()//, SDL_Color textColor)
{
	if (font_ == NULL) return false;
	SDL_Color textColor = { 255, 255, 255 };
	SDL_Color player1TextColor = { 0xD9, 0xD6, 0x02 };
	SDL_Color player2TextColor = { 0xD9, 0x00, 0x00 };

	std::vector<std::string> text{ "0","1","2","3","4","5","6","7","8","9","10","Player 01","Player 02"," : ","!! WINNER !! ", "TIE :-(" };

	int width = 0, height = 0;
	for (int i = 0; i < text.size(); i++)
	{
		//Render text surface
		SDL_Surface* textSurface = TTF_RenderText_Solid(font_, text[i].c_str(), (i == ScoreTexture::Player1) ? player1TextColor : ((i == ScoreTexture::Player2) ? player2TextColor : textColor));
		if (textSurface == NULL)
		{
			printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		}
		else
		{
			//Create texture from surface pixels
			SDL_Texture* mTexture = SDL_CreateTextureFromSurface(renderer_, textSurface);
			if (mTexture == NULL)
			{
				printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				//Get image dimensions
				width = textSurface->w;
				height = textSurface->h;
			}

			//Get rid of old surface
			SDL_FreeSurface(textSurface);

			scoreTextures_.push_back(Number(mTexture, width, height));
		}
	}

	return scoreTextures_.size() > 0;
}

void GameTextures::RenderNumber(int number, int x, int y, int cellSize, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	if (number <= scoreTextures_.size())
	{
		Number& numberTexture = scoreTextures_[number];
		int w = numberTexture.Width(), h = numberTexture.Height();

		//Set rendering space and render to screen
		SDL_Rect renderQuad = { x, y, w, h };

		//Set clip rendering dimensions
		if (clip != NULL)
		{
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}

		//Render to screen
		SDL_RenderCopyEx(renderer_, numberTexture.Texture(), clip, &renderQuad, angle, center, flip);
	}
}
void GameTextures::ScoreItemSize(int number, int& width, int& height)
{
	if (number <= scoreTextures_.size())
	{
		Number& numberTexture = scoreTextures_[number];
		width = numberTexture.Width();
		height = numberTexture.Height();
	}
}
void GameTextures::RenderImage(MatchingCard number, int x, int y, int cellSize, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	if (imageTextures_.size() == MatchingCard::LASTCARD)
	{
		PG2Texture* texture = imageTextures_[number];
		float scale = cellSize / (float)texture->Width(); 
		SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
		texture->Render(x, y, scale);//scale to cellSize?
		SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_NONE);
	}
}

void Number::free()
{
	if (texture_ != NULL)
	{
		SDL_DestroyTexture(texture_);
		texture_ = NULL;
	}
}
