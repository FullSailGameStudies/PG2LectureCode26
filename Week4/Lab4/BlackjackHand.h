#pragma once
#include <vector>
#include <string>
#include "BlackjackCard.h"

class BlackjackHand
{
public:
	BlackjackHand() : score_(0) {}
	virtual ~BlackjackHand();

	void AddCard(Card* blackJackCard);
	int Score() const { return score_; }
	virtual void Clear();

	const std::vector<Card*>& Cards() { return cards_; }

private:
	std::vector<Card*> cards_;
	int score_;

};

