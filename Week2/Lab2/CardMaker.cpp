#include "CardMaker.h"

void CardMaker::GetCardsForAllSuits(std::vector<Card>& cards)
{
	std::vector<std::string> suits{ "Hearts", "Clubs", "Diamonds", "Spades" };
	for (auto& suit : suits)
	{
		GetCardsForSuit(suit, cards);
	}
}

void CardMaker::GetCardsForSuit(const std::string& suit, std::vector<Card>& cards)
{
	std::vector<std::string> faces{ "A","2","3","4","5","6","7","8","9","10","J","Q","K" };
	for (auto& face : faces)
	{
		cards.push_back(Card(suit, face));
	}
}

Card CardMaker::GetRandomCardForSuit(const std::string& suit)
{
	std::vector<std::string> faces{ "A","2","3","4","5","6","7","8","9","10","J","Q","K" };
	int index = rand() % faces.size();
	return Card(suit, faces[index]);
}

void CardMaker::ShuffleCards(std::vector<Card>& cards)
{
	//
	//shuffle the vector of cards
	int index1 = 0, index2 = 0;
	int numberOfTimes = static_cast<int>(cards.size() * 3);
	for (size_t i = 0; i < numberOfTimes; i++)
	{
		index1 = rand() % cards.size();
		do
		{
			index2 = rand() % cards.size();
		} while (index2 == index1);
		std::swap(cards[index1], cards[index2]);
	}
}
