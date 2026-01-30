#pragma once
#include <string>

class Card
{
public:
	Card(const std::string& suit, const std::string& face)
	{
		_suit = suit;
		_face = face;
	}

	const std::string& Suit() const { return _suit; }
	void Suit(const std::string& suit) { _suit = suit; }

	const std::string& Face() const { return _face; }
	void Face(const std::string& face) { _face = face; }

	virtual int Value() const;
	int Compare(const Card& otherCard) const;

	void Print()const;

protected:
	std::string _suit;
	std::string _face;
};
