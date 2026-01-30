#pragma once
#include "BlackjackHand.h"
#include <fstream>
class BlackjackPlayer : public BlackjackHand
{
public:
	BlackjackPlayer() :
		name_(""), money_(1000), consecutiveWins_(0), winCount_(0) 
	{}
	BlackjackPlayer(std::string name) :
		name_(name), money_(1000), consecutiveWins_(0), winCount_(0)
	{
	}
	BlackjackPlayer(std::string name, int startingMoney, const std::string& fileName) :
		name_(name), money_(startingMoney), consecutiveWins_(0), winCount_(0), fileName_(fileName)
	{
	}

	//
	// TODO: Part A-2.1 Serialize method declaration
	//
	
	//
	// TODO: Part A-2.2 SavePlayer method declaration
	//

	//
	// TODO: Part A-3.1 Deserialize method declaration
	//

	//
	// TODO: Part A-3.2 constructor
	//

	//
	// TODO: Part A-3.3 LoadPlayer method declaration
	//


	void Win(int bet);
	void Loss();
	void Tie(int bet);
	int GetBet(int minBet, bool askUser = false);

	const std::string& Name() const { return name_; }
	int Money() const { return money_; }
	int ConsecutiveWins() const { return consecutiveWins_; }
	int WinCount() const { return winCount_; }

	const std::string& FileName() const { return fileName_; }

private:
	std::string name_;
	int money_;
	int consecutiveWins_;
	int winCount_;
	std::string fileName_;

};

