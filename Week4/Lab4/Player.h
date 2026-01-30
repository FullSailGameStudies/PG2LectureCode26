#pragma once
#include <string>
#include <vector>
#include "Card.h"

class Player
{
public:
	int GetScore() const { return score_; }
	void SetScore(int score) { score_ = score; }

	std::string GetName() const { return name_; }
	void SetName(std::string name) { name_ = name; }

	bool HasCards() const { return !pile_.empty(); }

	Card PopCard();
	void PushCard(Card card);
	void WonCards(std::vector<Card> cardsWon);

private:
	int score_;
	std::string name_;
	std::vector<Card> pile_;
	std::vector<Card> won_;
};

