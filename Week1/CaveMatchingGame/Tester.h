#pragma once
#include <vector>
#include "ResultsLib.h"
class Tester
{
public:
	const char* file;
	Tester() : file("Lab1.fslog")
	{
		std::vector<std::string> codeFiles{ "MatchingGame.cpp", "MatchingGame.h" };
		results::Log(file, codeFiles);
	}
};

