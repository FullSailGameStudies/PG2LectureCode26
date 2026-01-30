#pragma once
#include <vector>
#include "ResultsLib.h"
class Tester
{
public:
	const char* file;
	Tester() : file("Lab2.fslog")
	{
		std::vector<std::string> codeFiles{ "Lab2.cpp", "Sorter.cpp", "Sorter.h", "Searcher.cpp", "Searcher.h" };
		results::Log(file, codeFiles);
	}
};

