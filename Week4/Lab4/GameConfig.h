#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct GameConfig
{
	int NumberOfPlayers, NumberOfDecks, StartingMoney, MinimumBet;

	GameConfig() : NumberOfPlayers(1), NumberOfDecks(1), StartingMoney(10), MinimumBet(5)
	{	}

	//
	// TODO: Part A-1.1: LoadConfig
	//
};