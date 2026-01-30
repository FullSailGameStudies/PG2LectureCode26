#pragma once
#include <string>

class Card
{
public:
	Card(std::string suit, std::string face)
	{
		_suit = suit;
		_face = face;
	}

	std::string Suit() const { return _suit; }
	void Suit(std::string suit) { _suit = suit; }

	std::string Face() const { return _face; }
	void Face(std::string face) { _face = face; }

	int Value() const;
	int Compare(Card& otherCard) const;

	void Print()const;

private:
	std::string _suit;
	std::string _face;
};
