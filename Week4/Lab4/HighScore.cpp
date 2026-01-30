#include "HighScore.h"
#include "Console.h"
#include <fstream>
#include <sstream>
#include <iostream>

const char HIGHSCOREDELIM = '[';
std::vector<HighScore> HighScore::LoadHighScores(std::string fileName)
{
	std::vector<HighScore> highScores;

	std::ifstream ifs(fileName); // input file stream
	if (ifs)
	{
		std::string line;
		std::vector<std::string> lines;
		while (!ifs.eof())
		{
			std::getline(ifs, line);//each line is "Name,score"
			HighScore highScore(line, HIGHSCOREDELIM);

			//std::string name;
			//std::string scoreStr;
			//std::stringstream sPart(line);
			//std::getline(sPart, name, ',');
			//std::getline(sPart, scoreStr, ',');
			//int score = std::stoi(scoreStr);
			//HighScore highScore(name, score);

			highScores.push_back(highScore);
		}
		ifs.close();
	}
	else
		Console::WriteLine("The High Score file could not be opened.\n");

	return highScores;
 //   std::vector<HighScore> highScores;
 //   
 //   //
 //   // open the file
 //   // use rapidJson to read the file
 //   //
	//std::ifstream f(fileName);
	//std::stringstream buffer;
	//buffer << f.rdbuf();
	//f.close();

	//rapidjson::Document doc;
	//bool isGood = !doc.Parse(buffer.str().c_str()).HasParseError();

	//if (isGood && doc.IsArray())
	//{
	//	highScores.reserve(doc.Size());

	//	for (rapidjson::SizeType i = 0; i < doc.Size(); ++i)
	//	{
	//		rapidjson::Value& node = doc[i];
	//		HighScore highScore;
	//		highScore.deserialize(node);
	//		highScores.push_back(highScore);
	//	}
	//}

 //   return highScores;
}

void HighScore::SaveHighScores(std::string fileName,const std::vector<HighScore>& highScores)
{
	std::ofstream outFile(fileName);
	bool isFirst = true;
	for (auto& highScore : highScores)
	{
		if (!isFirst)
			outFile << "\n";
		highScore.Serialize(outFile, HIGHSCOREDELIM);

		isFirst = false;
	}

	outFile.close();
}

void HighScore::ShowHighScores(const std::vector<HighScore>& highScores)
{
	std::string name;
	Console::WriteLine("----HIGH SCORES----", ConsoleColor::Green);
	for (auto& highScore : highScores)
	{
		name = highScore.name();
		Console::Write(name);
		Console::SetCursorLeft(17);

		Console::WriteLine(std::to_string(highScore.score()), ConsoleColor::Yellow, ConsoleColor::Black);
	}
}

void HighScore::Serialize(std::ostream& file, char delim) const
{
	file << _name << delim << _score;
}

void HighScore::Deserialize(const std::string& csvData, char delim)
{
	std::stringstream parts(csvData);

	std::getline(parts, _name, delim);

	std::string scoreStr;
	std::getline(parts, scoreStr, delim);
	_score = std::stoi(scoreStr);
}


//bool HighScore::deserialize(const rapidjson::Value& obj)
//{
//	_score = obj["Score"].GetInt();
//	_name = obj["Name"].GetString();
//
//	return true;
//}
//
//bool HighScore::serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
//{
//	writer->StartObject();
//
//	writer->String("Name");
//	writer->String(_name.c_str());
//
//	writer->String("Score");
//	writer->Int(_score);
//
//	writer->EndObject();
//
//	return true;
//}
