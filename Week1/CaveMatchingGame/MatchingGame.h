#pragma once
#include "PG2Graphics.h"
#include <SDL_mixer.h>
#include "Tile.h"
#include <vector>


enum WinningPlayer
{
	P1, P2, NoOne
};

class MatchingGame
{
public:
	void Run(PG2Graphics& engine);

private:

	//
	// TODO: Part A-2.1: Add a method declaration for GetIndex
	//

	//
	// TODO: Part B-1.1: add a method declaration for BuildBoard
	//

	//
	// TODO: Part B-2.1: add a method declaration for DrawBoard
	//



	//------------------------------------------------------------------------------------------------------------------//
	//                                                                                                                  //
	//                       DO NOT CHANGE THE CODE BELOW                                                               //
	//                                                                                                                  //
	//------------------------------------------------------------------------------------------------------------------//
	void TestIndexing();
	void LoadSounds();
	void UnloadSounds();
	void ShowCursor(PG2Graphics& engine, int currentRow, int currentCol);
	void ShowScores(int player1Score, int player2Score, int width);
	void ShowWinner(WinningPlayer winningPlayer, int width);

	bool gameOver_;
	int currentPlayer_;
	std::vector<Mix_Chunk*> gameSounds_;
};

