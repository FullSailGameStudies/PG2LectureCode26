#include "BlackjackPlayer.h"
#include "Input.h"
#include <sstream>
#include <filesystem>
#include <iostream>


//
// TODO: Part A-2.1 Serialize method definition
//

//
// TODO: Part A-2.2 SavePlayer method definition
//

//
// TODO: Part A-3.1 Deserialize method definition
//

//
// TODO: Part A-3.3 LoadPlayer method definition
//




//----------------------------------------------------------------
//                                                              //
//		        DO NOT EDIT THE CODE BELOW                      //
//                                                              //

void BlackjackPlayer::Win(int bet)
{
	money_ += bet * 2;
	++consecutiveWins_;
	++winCount_;
}

void BlackjackPlayer::Loss()
{
	consecutiveWins_ = 0;
}

void BlackjackPlayer::Tie(int bet)
{
	money_ += bet;
	consecutiveWins_ = 0;
}

int BlackjackPlayer::GetBet(int minBet, bool askUser)
{
	int bet = minBet;
	if(askUser)
	{
		std::string msg = "Bet? (min: " + std::to_string(minBet) + " max: " + std::to_string(money_) + ") ";
		bet = Input::GetInteger(msg, minBet, money_);
	}
	money_ -= bet;
	return bet;
}