#include "BlackjackDeck.h"
#include "BlackjackCard.h"


Card* BlackjackDeck::MakeCard(const std::string& suit, const std::string& face)
{
	return new BlackjackCard(suit, face);
}
