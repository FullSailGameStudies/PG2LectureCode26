#include "Deck.h"
#include <fstream>
#include <sstream>
#include <iostream>

Deck::~Deck()
{
	Cleanup();
}

bool Deck::HasCards() const
{
	return not cards_.empty();
}

Card* Deck::DealCard()
{
	if (!HasCards())
		MakeCards();

	Card* card = cards_.back();
	cards_.pop_back();
	return card;
}

void Deck::Cleanup()
{
	for (int i = 0; i < cards_.size(); i++)
	{
		delete cards_[i];
	}
	cards_.clear();
}

void Deck::MakeCards()
{
	Cleanup();

	std::ifstream ifs("cards.csv"); // input file stream
	std::string line;
	if (ifs.is_open())
	{
		char delimiter = '<';

		std::string cardLine;
		std::string face;
		std::string suit;
		while (std::getline(ifs, cardLine))
		{
			std::stringstream cardStream(cardLine);
			std::getline(cardStream, face, delimiter);
			std::getline(cardStream, suit, delimiter);

			cards_.push_back(MakeCard(suit, face));
		}
	}
	else
		std::cout << "The cards file could not be opened.\n";
}

Card* Deck::MakeCard(const std::string& suit, const std::string& face)
{
	return new Card(suit, face);
}

void Deck::Shuffle()
{
	if (!HasCards())
		MakeCards();

	//shuffle the vector of cards
	int index1 = 0, index2 = 0;
	int numberOfSwaps = static_cast<int>(cards_.size()) * 3;
	for (size_t i = 0; i < numberOfSwaps; i++)
	{
		index1 = rand() % cards_.size();
		do
		{
			index2 = rand() % cards_.size();
		} while (index2 == index1);
		std::swap(cards_[index1], cards_[index2]);
	}
}
