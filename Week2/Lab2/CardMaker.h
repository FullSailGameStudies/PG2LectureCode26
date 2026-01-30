#pragma once
#include "Card.h"
#include <vector>

class CardMaker
{
public:
	static void GetCardsForAllSuits(std::vector<Card>& cards);
	static void GetCardsForSuit(const std::string& suit, std::vector<Card>& cards);
	static Card GetRandomCardForSuit(const std::string& suit);
	static void ShuffleCards(std::vector<Card>& cards);

private:

};

