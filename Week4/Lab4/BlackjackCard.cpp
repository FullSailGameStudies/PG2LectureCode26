#include "BlackjackCard.h"

int BlackjackCard::Value() const
{
	int value;
	if (sizeof(_face) == 3) //10 card
		value = 10;
	else
	{
		char first = _face[0];
		if (first == 'A')
			value = 1;
		else if (first == 'J' || first == 'Q' || first == 'K')
			value = 10;
		else
			value = std::stoi(_face);
	}

	return value;
}
