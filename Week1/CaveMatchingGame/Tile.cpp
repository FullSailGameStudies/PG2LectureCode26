#include "Tile.h"
#include "GameTextures.h"

void Tile::Draw(PG2Graphics& engine, int cellSize, int leftStart, int topStart, int cellBuffer) const
{
	int xo, yo;
	Uint8 red = 0, green = 0, blue = 0;
	SDL_Rect box;

	int halfBuffer = cellBuffer / 2;
	xo = col_ * cellSize; yo = row_ * cellSize;
	box.x = leftStart + halfBuffer + xo + 1;
	box.y = topStart + halfBuffer + yo + 1;

	bool showFace = IsBeingMatched(), isMatched = false;
	if (IsBeingMatched())
	{
		//show card
		GameTextures::RenderImage(MatchingCard::CardBack, box.x, box.y, cellSize - cellBuffer);
		GameTextures::RenderImage(cardType_, box.x, box.y, cellSize - cellBuffer);
	}
	else
	{
		if (IsMatched())
		{
			GameTextures::RenderImage(MatchingCard::CardBack, box.x, box.y, cellSize - cellBuffer);
			GameTextures::RenderImage(cardType_, box.x, box.y, cellSize - cellBuffer);
		}
		else
			GameTextures::RenderImage(MatchingCard::CardFront, box.x, box.y, cellSize - cellBuffer);
	}
}