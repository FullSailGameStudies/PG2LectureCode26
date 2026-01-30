#include "MatchingGame.h"
#include "Console.h"
#include <chrono>
#include <thread>

enum GameSound
{
	GameOver,
	Reveal,
	MakeMatch,
	NoMatch,
	MoveCursor,
	LASTSOUND
};

int range = 6;
int topStart = 50;
int leftStart = 0;
int cellSize = 0;
int cellMargin = 10;
int boardMargin = 10;
void MatchingGame::Run(PG2Graphics& engine)
{
	srand(static_cast<unsigned int>(time(NULL)));

	bool quit = false;
	gameOver_ = false;
	SDL_Event e;

	//------------------------------------------//
	//  Part A-1  Calling Methods               //
	//------------------------------------------//	

	// TODO: Part A-1: Game Controls
	// printing the game controls to the console window
	//	The title should be Green.
	//  The section names (Move, Select, Exit) should be Cyan
	//  The rest should be the default color
	//
	/* Expected output:
	Game Controls
	-------------
	Move:	WASD, arrow keys
	Select: spacebar
	Exit:	ESC key

	*/


	TestIndexing();

	//
	// create 16x16 game board
	//
	int boardSize = range * range;

	std::vector<int> cardCounts{ 6,6,6,2,2,6,2,6 };
	std::vector<Tile> board;
	board.reserve(boardSize);

	//
	// TODO: Part B-1.2: Call BuildBoard
	//


	LoadSounds();

	GameTextures::Initialize(engine.Renderer());

	int numberOfTiles = range * range;
	int totalMatches = numberOfTiles / 2;
	int winnerThreshold = totalMatches / 2;

	cellSize = 20;
	int width = engine.Width() - 2 * boardMargin, height = engine.Height() - topStart - 2 * boardMargin;
	int min = std::min(width, height);
	cellSize = min / range;
	leftStart = (engine.Width() - min) / 2;


	int player1_score = 0, player2_score = 0;
	int firstTile = 0;
	int secondTile = 0;
	currentPlayer_ = 1;
	int currentRow = 0, currentCol = 0, oldRow = 0, oldCol = 0;
	int numberCreepersFound = 0;
	bool walking;
	bool isFirstPick = true;
	WinningPlayer winner = P1;


	while (!quit)
	{
		walking = false;

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
			{
				quit = true;
			}
			else if (!gameOver_)
			{
				if (e.type == SDL_KEYUP && e.key.repeat == 0)
				{
					//
					// TODO: Part A-3: The Basics
					//
					switch (e.key.keysym.sym)
					{
					case SDLK_w:
					case SDLK_UP:
						//move up

						break;

					case SDLK_s:
					case SDLK_DOWN:
						//move down

						break;

					case SDLK_a:
					case SDLK_LEFT:
						//move left

						break;

					case SDLK_d:
					case SDLK_RIGHT:
						//move right

						break;

					case SDLK_SPACE:
						//select tile
						if (board.size() > 0)
						{
							int index = 0;
							//------------------------------------------//
							//  TODO: Part A-2.3 Using GetIndex         //
							//------------------------------------------//
							//  call your GetIndex method here and      // 
							//  assign the return value to index        //
							Tile& tile = board[index];


							if (!tile.IsMatched() && !tile.IsBeingMatched())
							{
								if (isFirstPick)
								{
									isFirstPick = false;

									tile.IsBeingMatched(true);
									firstTile = index;
									Mix_PlayChannel(-1, gameSounds_[GameSound::Reveal], 0);
								}
								else
								{
									isFirstPick = true;
									secondTile = index;

									Tile& tile1 = board[firstTile];
									Tile& tile2 = tile;

									tile2.IsBeingMatched(true);
									if (tile1.CardType() == tile2.CardType())
									{
										Tile::MatchTiles(tile1, tile2);

										//play happy sound
										Mix_PlayChannel(-1, gameSounds_[GameSound::MakeMatch], 0);

										//increment score for player
										if (currentPlayer_ == 1)
											player1_score++;
										else
											player2_score++;

										numberOfTiles -= 2;

										// scenario 1: all tiles are revealed
										if (numberOfTiles == 0)
										{
											gameOver_ = true;
										}

										// scenario 2: one player has a score that cannot be beat (they have a majority of the matches). > /2 of total matches
										//		EX: 18 total pairs. so if a player has > 9 matches
										if (player1_score > winnerThreshold || player2_score > winnerThreshold)
										{
											gameOver_ = true;
										}


										if (gameOver_)
										{
											//player winner sound
											Mix_PlayChannel(-1, gameSounds_[GameSound::GameOver], 0);

											winner = (player2_score > player1_score) ? P2 :
												(player2_score == player1_score) ? P1 :
												NoOne;
										}
									}
									else
									{
										//play sad sound
										Mix_PlayChannel(-1, gameSounds_[GameSound::NoMatch], 0);
										//
										// Part B-2.2: Call DrawBoard
										//


										engine.Present();

										if (currentPlayer_ == 1) currentPlayer_ = 2;
										else currentPlayer_ = 1;

										std::this_thread::sleep_for(std::chrono::milliseconds(3000));
										Tile::StopMatching(tile1, tile2);
									}
								}
							}
						}
						break;

					}
					if (walking)
					{
						Mix_PlayChannel(-1, gameSounds_[GameSound::MoveCursor], 0);
					}
				}
			}
			else if (gameOver_)
			{
				if (e.type == SDL_KEYUP && e.key.repeat == 0 && e.key.keysym.sym == SDLK_r)
				{
					gameOver_ = false;
					//
					// TODO: Part B-1.2: Call BuildBoard
					//
					player1_score = 0, player2_score = 0;
				}
			}
		}
		//------------------------------------------//
		//  Part A-1  Calling Methods               //
		//------------------------------------------//		

		// TODO: Part A-1: call ClearScreen on the engine object
		// TODO: Part C-1: use the default values

		//
		// TODO: Part B-2.2: Call DrawBoard
		//

		// TODO: Part A-1: call ShowCursor

		if (gameOver_)
			ShowWinner(winner, engine.Width());
		else
			ShowScores(player1_score, player2_score, engine.Width());


		// TODO: Part A-1: call Present on the engine object
	}
	UnloadSounds();
	GameTextures::Cleanup();
}

//
// TODO: Part A-2.1: Add a method definition for GetIndex
//

void MatchingGame::TestIndexing()
{
	bool good = true;
	int correctIndex = 0, index = 0;
	for (int row = 0; row < range; row++)
	{
		for (int col = 0; col < range; col++)
		{
			//------------------------------------------//
			//  TODO: Part A-2.2  Testing GetIndex      //
			//------------------------------------------//
			//  call your GetIndex method here and      // 
			//  assign the return value to index        //

			if (index != correctIndex)
			{
				std::cout << "GetIndex ERROR!\nCorrect Index: " << correctIndex << "\tGetIndex result: " << index << "\n";
				good = false;
				break;
			}
			correctIndex++;
		}
		if (!good) break;
	}
	if (good)
		std::cout << "\nGetIndex test PASSES!\n";
	else
		std::cout << "\nGetIndex test FAILS!\n";
}

//
// TODO: Part B-1.1: add a method definition for BuildBoard
//

//
// TODO: Part B-2.1: add a method definition for DrawBoard
//


//------------------------------------------------------------------------------------------------------------------//
//                                                                                                                  //
//                       DO NOT CHANGE THE CODE BELOW                                                               //
//                                                                                                                  //
//------------------------------------------------------------------------------------------------------------------//
void MatchingGame::LoadSounds()
{
	if (gameSounds_.capacity() == 0)
		gameSounds_.reserve(GameSound::LASTSOUND);

	gameSounds_.push_back(Mix_LoadWAV("MOB_VILLAGER_YES2.ogg"));//gameover
	//gameSounds_.push_back(Mix_LoadWAV("RANDOM_POP.ogg"));//try match
	gameSounds_.push_back(Mix_LoadWAV("tap-b.ogg"));//try match
	gameSounds_.push_back(Mix_LoadWAV("MOB_VILLAGER_YES3.ogg"));//make match
	gameSounds_.push_back(Mix_LoadWAV("MOB_VILLAGER_NO3.ogg"));//no match
	gameSounds_.push_back(Mix_LoadWAV("click-b.ogg"));//move cursor
}

void MatchingGame::UnloadSounds()
{
	for (auto& chunk : gameSounds_)
	{
		Mix_FreeChunk(chunk);
	}
	gameSounds_.clear();
}


void MatchingGame::ShowCursor(PG2Graphics& engine, int currentRow, int currentCol)
{
	int xo, yo;
	SDL_Rect box;

	if (currentPlayer_ == 1)
		SDL_SetRenderDrawColor(engine.Renderer(), 0xD9, 0xD6, 0x02, 0xFF);
	else
		SDL_SetRenderDrawColor(engine.Renderer(), 0xD9, 0x00, 0x00, 0xFF);

	int halfBuffer = cellMargin / 2;
	//xo = col_ * cellSize; yo = row_ * cellSize;
	//box.x = leftStart + halfBuffer + xo + 1;
	//box.y = topStart + halfBuffer + yo + 1;

	xo = currentCol * cellSize; yo = currentRow * cellSize;
	box.x = leftStart + halfBuffer + xo + 1;// +xo + 2;
	box.y = topStart + halfBuffer + yo + 1;// + yo + 2;
	box.w = cellSize - 2;
	box.h = cellSize - 2;

	GameTextures::RenderImage(MatchingCard::Cursor, box.x, box.y, cellSize - cellMargin);
	//SDL_RenderFillRect(engine.Renderer(), &box);
}

void MatchingGame::ShowScores(int player1Score, int player2Score, int width)
{
	int player1X = leftStart, player2X = width - leftStart;
	int playerTop = topStart;

	int w = 0, h = 0;
	GameTextures::ScoreItemSize(ScoreTexture::Player1, w, h);
	GameTextures::RenderNumber(ScoreTexture::Player1, player1X, playerTop - h, cellSize);

	int sepW = 0, sepH = 0;
	GameTextures::ScoreItemSize(ScoreTexture::Separator, sepW, sepH);
	GameTextures::RenderNumber(ScoreTexture::Separator, player1X + w, playerTop - h, cellSize);

	GameTextures::RenderNumber(player1Score, player1X + w + sepW, playerTop - h, cellSize);


	int scoreW = 0, scoreH = 0;
	GameTextures::ScoreItemSize(player2Score, scoreW, scoreH);
	int scoreDiff = scoreW + scoreW / 2;
	GameTextures::ScoreItemSize(ScoreTexture::Player2, w, h);
	GameTextures::RenderNumber(ScoreTexture::Player2, player2X - w - sepW - scoreDiff, playerTop - h, cellSize);
	GameTextures::RenderNumber(ScoreTexture::Separator, player2X - sepW - scoreDiff, playerTop - h, cellSize);
	GameTextures::RenderNumber(player2Score, player2X - scoreDiff, playerTop - h, cellSize);

	playerTop = playerTop - h - 3;
	if (currentPlayer_ == 1)
		GameTextures::RenderImage(MatchingCard::CurrentPlayer, 5, playerTop, h);
	else
		GameTextures::RenderImage(MatchingCard::CurrentPlayer, player2X - w - sepW - scoreDiff - 31, playerTop, h);
}

void MatchingGame::ShowWinner(WinningPlayer winningPlayer, int width)
{
	int winnerX = width / 2;
	int winnerY = topStart;


	int w = 0, h = 0, pW = 0, pH = 0;
	if (winningPlayer == WinningPlayer::NoOne)
	{
		GameTextures::ScoreItemSize(ScoreTexture::Tie, w, h);
		GameTextures::RenderNumber(ScoreTexture::Tie, winnerX - w / 2, winnerY - h, cellSize);
	}
	else
	{
		GameTextures::ScoreItemSize(ScoreTexture::Winner, w, h);

		if (winningPlayer == WinningPlayer::P1)
			GameTextures::ScoreItemSize(ScoreTexture::Player1, pW, pH);
		else
			GameTextures::ScoreItemSize(ScoreTexture::Player2, pW, pH);

		winnerX -= (w + pW) / 2;
		GameTextures::RenderNumber(ScoreTexture::Winner, winnerX, winnerY - h, cellSize);
		if (winningPlayer == WinningPlayer::P1)
			GameTextures::RenderNumber(ScoreTexture::Player1, winnerX + w, winnerY - h, cellSize);
		else
			GameTextures::RenderNumber(ScoreTexture::Player2, winnerX + w, winnerY - h, cellSize);
	}
}
