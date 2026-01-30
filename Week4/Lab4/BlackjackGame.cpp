#include "BlackjackGame.h"
#include "GameTextures.h"
#include <iostream>

void BlackjackGame::ShowPlayerStats(const BlackjackPlayer& player) const
{
	//
	// TODO: Part B-1.1 show player stats
	//

}

void BlackjackGame::DealCards(BlackjackPlayer& player)
{
	//
	// TODO: Part B-1.2 handle dealing logic
	//

}

void BlackjackGame::DealersTurn()
{
	//
	// TODO: Part B-1.3 handle dealer's logic
	//

}

GameResult BlackjackGame::EndGame(BlackjackPlayer& player, int bet)
{
	GameResult result = GameResult::Loss;

	//
	// TODO: Part B-1.4 write the win/loss/tie scenarios
	//


	switch (result)
	{
	case Win:
		player.Win(bet);
		break;
	case Loss:
		player.Loss();
		break;
	case Tie:
		player.Tie(bet);
		break;
	default:
		break;
	}

	return result;
}

void BlackjackGame::Play(BlackjackPlayer& player)
{
	//Screen dimension constants
	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGHT = 683;

	dealer_ = new BlackjackDealer();
	deck_ = new BlackjackDeck(numberOfDecks_);
	deck_->Shuffle();
	DealCards(player);

	bool playAgain = true;

	std::vector<std::string> playingOptions{
		"1. Hit",
		"2. Stand",
		"3. Quit" };

	std::vector<std::string> playAgainOptions{
		"1. Play Another Round",
		"2. Leave Table" };


	int bet = player.GetBet(minBet_);// FUTURE TODO:  handle user input for bet.  
	ShowGameMenu("Blackjack Game Option", playingOptions);


	engine_ = new PG2Graphics(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!engine_->Init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		GameTextures::Initialize(engine_->Renderer());
		ShowGame(player);

		GameState gameState = GameState::Playing;
		bool quit = false;
		SDL_Event e;
		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
				{
					quit = true;
					playAgain = false;
				}
				else if (e.type == SDL_KEYUP && e.key.repeat == 0)
				{
					if (gameState == GameState::Playing)
					{
						bool updateScreen = false;
						GameResult result = GameResult::Loss;
						switch (e.key.keysym.sym)
						{
						case SDLK_1: //hit
						{
							updateScreen = true;

							//
							// TODO: Part B-2.1 handle player turn: hit
							//

							break;
						}
						case SDLK_2: //Stand
						{
							updateScreen = true;

							//
							// TODO: Part B-2.2 handle player turn: stand
							//

							break;
						}
						case SDLK_3: //quit the game
							playAgain = false;
							quit = true;
							break;

						}

						if (updateScreen)
						{
							ShowGame(player);
							if (gameState != GameState::Playing)
							{
								// show win/loss/tie screen
								ShowResult(player, result);
								ShowPlayerStats(player);
								ShowGameMenu("Do you want to play again?", playAgainOptions);

								//
								// TODO: Part B-2.3 save the player data
								//
							}
						}
					}
					else //playAgain
					{
						switch (e.key.keysym.sym)
						{
						case SDLK_1: //Play another round
						{
							// reset the game board
							playAgain = true;
							gameState = GameState::Playing;
							player.Clear();
							dealer_->Clear();
							cardAngles_.clear();

							bet = player.GetBet(minBet_);  // FUTURE TODO:  handle user input for bet.
							DealCards(player);
							ShowGame(player);
							ShowGameMenu("Blackjack Game Option", playingOptions);
							break;
						}
						case SDLK_2: //leave table
							quit = true;
							playAgain = false;
							break;

						}
					}
				}
			}
		}
		GameTextures::Cleanup();
	}

	engine_->Close();
	Cleanup();
}



//----------------------------------------------------------------
//                                                              //
//		        DO NOT EDIT THE CODE BELOW                      //
//                                                              //

BlackjackGame::BlackjackGame(int numberOfPlayers, int numberOfDecks, int minBet) :
	numberOfPlayers_(numberOfPlayers),
	numberOfDecks_(numberOfDecks),
	minBet_(minBet),
	deck_(nullptr),
	dealer_(nullptr),
	engine_(nullptr)
{
}

BlackjackGame::~BlackjackGame()
{
	Cleanup();
}

void BlackjackGame::Cleanup()
{
	if (deck_ != nullptr)
	{
		delete deck_;
		deck_ = nullptr;
	}
	if (dealer_ != nullptr)
	{
		delete dealer_;
		dealer_ = nullptr;
	}
	//for (size_t i = 0; i < players_.size(); i++)
	//{
	//	if (players_[i]->Name().size() == 0) //only delete players created by the game
	//		delete players_[i];
	//}
	//players_.clear();
	if (engine_ != nullptr)
	{
		delete engine_;
		engine_ = nullptr;
	}
}


void BlackjackGame::ShowGameMenu(const std::string& title, const std::vector<std::string>& menuOptions) const
{
	std::cout << "\n\n" << title << "\n";
	for (auto& option : menuOptions)
	{
		std::cout << option << "\n";
	}
	std::cout << "\nSelect an option: \n";
}

void BlackjackGame::ShowGame(BlackjackPlayer& player)
{
	float scale = 1.15f;
	engine_->ClearScreen(50, 150, 50, 255);

	GameTextures::RenderBackground(0, 0);
	pos cardSize = GameTextures::CardSize(scale);

	//
	// PLAYER Cards
	//
	//BlackjackPlayer* player = players_[0];// FUTURE TODO: update to handle multiple players
	int x = 473, y = 443;//player starting position

	auto& cards = player.Cards();
	if (cardAngles_.size() == 0)
	{
		std::vector<double> angles;
		cardAngles_.push_back(angles);
		cardAngles_.push_back(angles);
	}
	for (int i = 0; i < cards.size(); i++)
	{
		if (i == cardAngles_[0].size())
		{
			double cardAngle = rand() % 8;
			cardAngle = (rand() % 100 < 50) ? -1 * cardAngle : cardAngle;
			cardAngles_[0].push_back(cardAngle);
		}
		GameTextures::RenderImage(cards[i]->Face(), cards[i]->Suit(), x, y, scale, NULL, cardAngles_[0][i]);
		x += static_cast<int>(cardSize.x * 0.25);
		y += 5;
	}
	std::cout << "Player Score: " << player.Score() << "\n";

	//
	// DEALER Cards
	//
	x = 473, y = 37;//dealer stating position
	auto& dealercards = dealer_->Cards();
	bool reveal = dealer_->Reveal();
	if (reveal)
		std::cout << "Dealer Score: " << dealer_->Score() << "\n";

	for (int i = 0; i < dealercards.size(); i++)
	{
		if (i == cardAngles_[1].size())
		{
			double cardAngle = rand() % 8;
			cardAngle = (rand() % 100 < 50) ? -1 * cardAngle : cardAngle;
			cardAngles_[1].push_back(cardAngle);
		}
		if (i == 0)
		{
			if (reveal)
				GameTextures::RenderImage(dealercards[i]->Face(), dealercards[i]->Suit(), x, y, scale, NULL, cardAngles_[1][i]);
			else
				GameTextures::RenderImage("", "", x, y, scale, NULL, cardAngles_[1][i]);
		}
		else
			GameTextures::RenderImage(dealercards[i]->Face(), dealercards[i]->Suit(), x, y, scale, NULL, cardAngles_[1][i]);
		x += static_cast<int>(cardSize.x * 0.25);
		y += 5;
	}

	engine_->Present();
}


void BlackjackGame::ShowResult(const BlackjackPlayer& player, GameResult result) const
{
	float scale = 1.15f;

	//BlackjackPlayer* player = players_[0];// FUTURE TODO: update to handle multiple players
	int x = 511, y = 435;//player starting position
	pos cardSize = GameTextures::CardSize(scale);

	switch (result)
	{
	case Win:
		GameTextures::RenderNumber(ScoreTexture::Won, x, y);
		std::cout << "Player wins!!\n";
		break;
	case Loss:
		GameTextures::RenderNumber(ScoreTexture::Lost, x, y);
		std::cout << "Player loses.\n";
		break;
	case Tie:
		GameTextures::RenderNumber(ScoreTexture::Tied, x, y);
		std::cout << "It's a tie.\n";
		break;
	default:
		break;
	}


	engine_->Present();
}