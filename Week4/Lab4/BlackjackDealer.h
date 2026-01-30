#pragma once
#include "BlackjackHand.h"

class BlackjackDealer : public BlackjackHand
{
public:
	BlackjackDealer() : reveal_(false) {}
	void Reveal(bool showAllCards) { reveal_ = showAllCards; }
	bool Reveal() const { return reveal_; }

	void Clear() override;

private:
	bool reveal_;
};

