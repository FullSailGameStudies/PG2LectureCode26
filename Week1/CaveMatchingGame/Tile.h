#pragma once
#include "GameTextures.h"

class Tile
{
public:
	Tile() : 
		isMatched_(false), 
		isBeingMatched_(false), 
		cardType_(LASTCARD),
		row_(0),
		col_(0)
	{}
	Tile(int row, int col, MatchingCard cardType) :
		row_(row),
		col_(col),
		cardType_(cardType),
		isMatched_(false),
		isBeingMatched_(false)
	{
	}
	int Row() const { return row_; }
	void Row(int newRow) { row_ = newRow; }
	int Column() const { return col_; }
	void Column(int newColumn) { col_ = newColumn; }
	MatchingCard CardType() const { return cardType_; }
	bool IsMatched() const { return isMatched_; }
	void IsMatched(bool isMatched) { isMatched_ = isMatched; }
	bool IsBeingMatched() const { return isBeingMatched_; }
	void IsBeingMatched(bool isBeingRevealed) { isBeingMatched_ = isBeingRevealed; }

	void MatchTile()
	{
		isMatched_ = true;
		isBeingMatched_ = false;
	}

	static void MatchTiles(Tile& tile1, Tile& tile2)
	{
		tile1.MatchTile();
		tile2.MatchTile();
	}
	static void StopMatching(Tile& tile1, Tile& tile2)
	{
		tile1.IsBeingMatched(false);
		tile2.IsBeingMatched(false);
	}

	void Draw(PG2Graphics& engine, int cellSize, int leftStart = 10, int topStart = 30, int cellBuffer = 5) const;


private:
	int row_, col_;
	bool isMatched_, isBeingMatched_;
	MatchingCard cardType_;
};

