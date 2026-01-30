#pragma once
//#include "JSONIncludes.h"
#include <string>
#include <vector>
#include <fstream>

class HighScore
{
public:
	HighScore(std::string name, int score)
	{
		_name = name;
		_score = score;
	}
	HighScore(const std::string& csvData, char delim)
	{
		Deserialize(csvData, delim);
	}

	std::string name() const { return _name; }
	void name(std::string name) { _name = name; }

	int score() const { return _score; }
	void score(int score) { _score = score; }

	static std::vector<HighScore> LoadHighScores(std::string fileName);
	static void SaveHighScores(std::string fileName, const std::vector<HighScore>& highScores);
	static void ShowHighScores(const std::vector<HighScore>& highScores);

private:
	std::string _name;
	int _score = 0;

	void Deserialize(const std::string& csvData, char delim);
	void Serialize(std::ostream& file, char delim) const;
};

