#pragma once
#include <vector>
#include "Card.h"

class Deck
{
public:
	virtual ~Deck();

	bool HasCards() const;
	Card* DealCard();
	void Shuffle();

protected:
	std::vector<Card*> cards_;

	void Cleanup();
	void MakeCards();
	virtual Card* MakeCard(const std::string& suit, const std::string& face);
};

