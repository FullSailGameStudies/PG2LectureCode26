#include "Card.h"
#include <iostream>

int Card::Compare(const Card& otherCard) const
{
	int pValue = Value();
	int cValue = otherCard.Value();
	if (pValue > cValue)
		return 1;//player wins
	else if (pValue < cValue)
		return -1;//npc wins 

	return 0;
}

void Card::Print() const
{
	std::cout << _face << " " << _suit;
}

int Card::Value() const
{
	int value;
	if (sizeof(_face) == 3) //10 card
		value = 10;
	else
	{
		char first = _face[0];
		if (first == 'A')
			value = 1;
		else if (first == 'J')
			value = 11;
		else if (first == 'Q')
			value = 12;
		else if (first == 'K')
			value = 13;
		else
			value = std::stoi(_face);
	}

	return value;
	//return (int)face;
}