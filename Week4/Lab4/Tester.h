#pragma once
#include <vector>
#include "ResultsLib.h"
class Tester
{
public:
	const char* file;
	Tester() : file("..\\..\\Lab4\\Blackjack.fslog")
	{
		std::vector<std::string> codeFiles
		{
			"..\\..\\Lab4\\Blackjack.cpp",
			"..\\..\\Lab4\\GameConfig.h",
			"..\\..\\Lab4\\BlackjackPlayer.cpp" ,
			"..\\..\\Lab4\\BlackjackPlayer.h",
			"..\\..\\Lab4\\BlackjackGame.cpp"
		};
		results::Log(file, codeFiles);
	}
};

