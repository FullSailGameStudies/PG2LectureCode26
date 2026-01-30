#pragma once
#include "Deck.h"
class BlackjackDeck : public Deck
{
public:
	BlackjackDeck(int numberOfDecks = 1) : numberOfDecks_(numberOfDecks)
	{	}

protected:
	Card* MakeCard(const std::string& suit, const std::string& face) override;

private:
	int numberOfDecks_;
};

