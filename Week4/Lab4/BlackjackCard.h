#pragma once
#include "Card.h"
class BlackjackCard : public Card
{
public:
	BlackjackCard(const std::string& suit, const std::string& face)
		: Card(suit, face)
	{ }

	int Value() const override;
};

