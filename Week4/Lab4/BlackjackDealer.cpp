#include "BlackjackDealer.h"

void BlackjackDealer::Clear()
{
	BlackjackHand::Clear();
	reveal_ = false;
}
