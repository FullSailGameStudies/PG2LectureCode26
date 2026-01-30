#pragma once
#include <string>
#include <vector>
#include "Card.h"
#include "HighScore.h"

class WarGame
{

public:
	WarGame(std::string cardsFile); 

	static void PlayGame(std::string playerName, std::string fileName, std::vector<HighScore>& highScores);
	static void ShowCards();

	static const std::vector<Card>& Cards() { return _cards; }

private:
	static std::vector<Card> _cards;


	static void LoadCards(std::string fileName);
	static void Shuffle();
};

