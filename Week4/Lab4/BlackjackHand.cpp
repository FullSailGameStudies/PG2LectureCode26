#include "BlackjackHand.h"

BlackjackHand::~BlackjackHand()
{
	Clear();
}

void BlackjackHand::AddCard(Card* blackJackCard)
{
	cards_.push_back(blackJackCard);

	//update score
	score_ = 0;
	bool hasAces = false;
	for (auto card : cards_)
	{
		score_ += card->Value();
		if (card->Face() == "A") hasAces = true;
	}
	if (hasAces && score_ < 12) score_ += 10;//add 10 for 1 ace
}

void BlackjackHand::Clear()
{
	score_ = 0;
	for (int i = 0; i < cards_.size(); i++)
	{
		delete cards_[i];
	}
	cards_.clear();
}