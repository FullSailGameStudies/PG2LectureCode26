#include "Player.h"

Card Player::PopCard()
{
	Card card = pile_.back();
	pile_.pop_back();
	return card;
}

void Player::PushCard(Card card)
{
	pile_.push_back(card);
}

void Player::WonCards(std::vector<Card> cardsWon)
{
	won_.insert(won_.end(), cardsWon.begin(), cardsWon.end());
	score_ = won_.size();
}
