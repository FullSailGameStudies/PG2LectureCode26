#include <iostream>
#include "Console.h"
#include "Input.h"
#include "WarGame.h"
#include "HighScore.h"
#include "Tester.h"
#include "BlackjackGame.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include "GameConfig.h"

int main(int argc, char* args[])
{
	srand(static_cast<unsigned int>(time(NULL)));

	Tester tests;
	Console::ResizeWindow(150, 30);

	std::string playerExtension = ".psv";
	int menuSelection = 0;
	std::vector<std::string> menuOptions{ "1. New Player", "2. Load Player", "3. List Players", "4. Play Blackjack", "5. Exit" };

	//
	// TODO: Part A-1.2: Load Game Config
	//
	std::string configFile = "blackjackConfig.csv";
	GameConfig config;

	BlackjackPlayer p1;

	do
	{
		Console::Clear();
		if (p1.Name().size() > 0)
		{
			std::cout << "Current player: " << p1.Name() << "\n";
		}
		menuSelection = Input::GetMenuSelection(menuOptions);
		Console::Clear();

		switch (menuSelection)
		{
		case 1:
		{
			//
			// TODO: Part A-2.3: SavePlayer
			//

			break;
		}
		case 2:
		{
			//
			// TODO: Part A-3.4: LoadPlayer
			//

			break;
		}
		case 3:
		{
			std::string path = "./"; //use current directory

			try {
				for (const auto& entry : std::filesystem::directory_iterator(path)) {
					if (entry.is_regular_file() && entry.path().extension() == playerExtension) {
						std::cout << entry.path().filename() << std::endl;
					}
				}
			}
			catch (const std::filesystem::filesystem_error& e) {
				std::cerr << "Filesystem error: " << e.what() << std::endl;
			}
			catch (const std::exception& e) {
				std::cerr << "General error: " << e.what() << std::endl;
			}

			break;
		}
		case 4:
		{
			if (not p1.Name().empty())
			{
				BlackjackGame game(config.NumberOfPlayers, config.NumberOfDecks, config.MinimumBet);
				game.Play(p1);
			}
			else
			{
				std::cout << "Please load a player first.\n";
			}
			break;
		}

		}

		Input::PressEnter();
	} while (menuSelection != menuOptions.size());

	return 0;
}