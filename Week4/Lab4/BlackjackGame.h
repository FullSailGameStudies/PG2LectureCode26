#pragma once
#include <string>
#include <vector>
#include "PG2Graphics.h"
#include "BlackjackPlayer.h"
#include "BlackjackDealer.h"
#include "BlackjackDeck.h"

enum GameState
{
	Playing, PlayAgain
};
enum GameResult
{
	Win, Loss, Tie
};


class BlackjackGame
{
public:
	BlackjackGame(int numberOfPlayers, int numberOfDecks, int minBet);
	~BlackjackGame();
	void Play(BlackjackPlayer& player);

private:
	int numberOfPlayers_;
	int numberOfDecks_;
	int minBet_;
	std::vector<std::vector<double>> cardAngles_;
	BlackjackDealer* dealer_;
	BlackjackDeck* deck_;
	PG2Graphics* engine_;

	void Cleanup();
	void ShowGameMenu(const std::string& title, const std::vector<std::string>& menuOptions) const;

	void DealersTurn();
	void DealCards(BlackjackPlayer& player);
	void ShowGame(BlackjackPlayer& player);
	void ShowResult(const BlackjackPlayer& player, GameResult result) const;
	GameResult EndGame(BlackjackPlayer& player, int bet);
	void ShowPlayerStats(const BlackjackPlayer& player) const;

};

