#include <iostream>
#include <vector>
#include <string>
#include "PG2Graphics.h"
#include "Console.h"
#include "Sorter.h"
#include "Searcher.h"
#include <map>
#include <Input.h>
#include "CardMaker.h"
#include <GameTextures.h>
#include "Tester.h"


//Screen dimension constants
const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 480;

void ShowMenu(const std::vector<std::string>& menuOptions)
{
	std::cout << "\n\nLab 2 Menu: \n";
	for (auto& option : menuOptions)
	{
		std::cout << option << "\n";
	}
	std::cout << "\nSelect an option: \n";
}

void ShowCards(PG2Graphics& engine, const std::vector<Card>& cards, int row = 0)
{
	float scale = 1.0F;

	pos cardSize = GameTextures::CardSize(scale);
	int x = 5;
	int y = cardSize.y * row + 5 + 5 * row;

	std::string suit = "";
	for (auto& card : cards)
	{
		GameTextures::RenderImage(card.Face(), card.Suit(), x, y, scale);
		x += cardSize.x + 5;
	}

}

const int A2_WIDTH = 1024;
const int A2_HEIGHT = 550;
int main(int argc, char* args[])
{
	Tester tests;
	srand(static_cast<unsigned int>(time(NULL)));

	//
	//create the 13 cards for 1 suit
	std::vector<Card> clubs;
	std::string suit = "Clubs";
	CardMaker::GetCardsForSuit(suit, clubs);
	CardMaker::ShuffleCards(clubs);

	std::vector<Card> allSuits;
	CardMaker::GetCardsForAllSuits(allSuits);
	CardMaker::ShuffleCards(allSuits);



	//
	// TODO: Part B-2 Build a map with the suit as the key and a vector of the cards for the suit as the value
	//
	std::map<std::string, std::vector<Card>> groups;



	PG2Graphics engine(A2_WIDTH, A2_HEIGHT);
	if (!engine.Init("Part A-2"))
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		Console::WriteLine("Part A-2 Sorting", ConsoleColor::Green);
		Console::WriteLine("MergeSort Cards.");


		GameTextures::Initialize(engine.Renderer());

		std::vector<std::string> menuOptions{
			"1. BubbleSorted Cards", "2. MergeSorted Cards", "3. Search Cards",
			"4. Group Cards: Show All", "5. \tGroup Cards: Show Hearts","6. \tGroup Cards: Show Clubs","7. \tGroup Cards: Show Diamonds","8. \tGroup Cards: Show Spades",
			"9. Remove Suit",
			"0. Exit" };
		ShowMenu(menuOptions);



		engine.ClearScreen(0, 0, 0, 0xFF);
		bool quit = false;
		SDL_Event e;
		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
				{
					quit = true;
				}
				else if (e.type == SDL_KEYUP && e.key.repeat == 0)
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_1:
					{
						std::vector<Card> bubbleSortedCards = clubs;
						//
						// TODO: Part A-1.2
						// call your BubbleSort
						//
						Sorter sorter;

						float scale = 1.0F;
						engine.ClearScreen(50, 150, 50, 255);

						pos cardSize = GameTextures::CardSize(scale);
						int x = 5;
						int y = 5;

						std::string suit = "";
						for (auto& card : bubbleSortedCards)
						{
							if (suit == "") suit = card.Suit();
							else if (suit != card.Suit())
							{
								suit = card.Suit();
								x = 5;
								y += cardSize.y + 5;
							}

							GameTextures::RenderImage(card.Face(), card.Suit(), x, y, scale);
							x += cardSize.x + 5;
						}

						//Update screen
						engine.Present();
						break;
					}
					case SDLK_2:
					{
						std::vector<Card> mergeSortedCards = clubs;
						//
						// TODO: Part A-2.3 
						// call your MergeSort
						//
						Sorter sorter;

						float scale = 1.0F;
						engine.ClearScreen(50, 150, 50, 255);

						pos cardSize = GameTextures::CardSize(scale);
						int x = 5;
						int y = cardSize.y + 5;

						std::string suit = "";
						for (auto& card : mergeSortedCards)
						{
							if (suit == "") suit = card.Suit();
							else if (suit != card.Suit())
							{
								suit = card.Suit();
								x = 5;
								y += cardSize.y + 5;
							}

							GameTextures::RenderImage(card.Face(), card.Suit(), x, y, scale);
							x += cardSize.x + 5;
						}

						//Update screen
						engine.Present();
						break;
					}
					case SDLK_3:
					{
						std::vector<Card> sortedCards;
						CardMaker::GetCardsForSuit("Clubs", sortedCards);
						Card randoCard = CardMaker::GetRandomCardForSuit("Clubs");
						//
						// TODO: Part B-1.2
						// call BinarySearch to find the index of the card in the sorted vector
						// print the index of the card to the console
						//
						int index = -1;
						Searcher searcher;


						float scale = 1.0F;
						engine.ClearScreen(50, 150, 50, 255);

						pos cardSize = GameTextures::CardSize(scale);
						int x = 5;
						int y = 5;

						std::string suit = "";
						for (auto& card : sortedCards)
						{
							if (suit == "") suit = card.Suit();
							else if (suit != card.Suit())
							{
								suit = card.Suit();
								x = 5;
								y += cardSize.y + 5;
							}

							GameTextures::RenderImage(card.Face(), card.Suit(), x, y, scale);
							x += cardSize.x + 5;
						}
						y += cardSize.y + 5;
						x = (cardSize.x + 5) * index + 5;
						GameTextures::RenderImage(randoCard.Face(), randoCard.Suit(), x, y, scale);

						//Update screen
						engine.Present();
						break;
					}
					case SDLK_4:
					{
						engine.ClearScreen(50, 150, 50, 255);
						//
						// TODO: Part B-3
						// loop over the map
						//	  call ShowCards for the vector of each suit
						//		1st parameter: pass the engine variable
						//      2nd parameter: pass the vector for each suit to the ShowCards method.
						//      3rd parameter: pass the row. each suit should be printed on a separate row.
						//    increment row after calling ShowCards
						//		
						int row = 0;

						//Update screen
						engine.Present();
						break;
					}
					case SDLK_5:
					{
						//
						// TODO: Part C-1.1
						// find the Hearts suit. 
						//		if found, call ShowCards for the Hearts vector
						//
						engine.ClearScreen(50, 150, 50, 255);

						//Update screen
						engine.Present();
						break;
					}
					case SDLK_6:
					{
						//
						// TODO: Part C-1.2
						// find the Clubs suit. 
						//		if found, call ShowCards for the Clubs vector
						//
						engine.ClearScreen(50, 150, 50, 255);

						//Update screen
						engine.Present();
						break;
					}
					case SDLK_7:
					{
						//
						// TODO: Part C-1.3
						// find the Diamonds suit. 
						//		if found, call ShowCards for the Diamonds vector
						//
						engine.ClearScreen(50, 150, 50, 255);

						//Update screen
						engine.Present();
						break;
					}
					case SDLK_8:
					{
						//
						// TODO: Part C-1.4
						// find the Spades suit. 
						//		if found, call ShowCards for the Spades vector
						//
						engine.ClearScreen(50, 150, 50, 255);

						//Update screen
						engine.Present();
						break;
					}
					case SDLK_9:
					{
						//
						// TODO: Part C-2
						// find the Clubs suit. 
						//		if found,
						//			erase the suit from the map
						//			loop over the map and call the ShowCards for the vector of each Suit in the map
						//		else if not found
						//			print to the Console that "Clubs was not found"
						//
						engine.ClearScreen(50, 150, 50, 255);
						int row = 0;


						//Update screen
						engine.Present();
						break;
					}

					case SDLK_0:
					{
						quit = true;
						break;
					}

					}
				}
			}

		}


		GameTextures::Cleanup();
	}
	engine.Close();

	return 0;
}
