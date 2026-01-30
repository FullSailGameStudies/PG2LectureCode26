#include "WarGame.h"
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "HighScore.h"
#include "Input.h"
#include <Player.h>
#include <Console.h>


std::vector<Card> WarGame::_cards;

WarGame::WarGame(std::string cardsFile)
{
    LoadCards(cardsFile);
}

void WarGame::Shuffle()
{
    int ndx1, ndx2;
    srand((unsigned int)time(NULL));

    for (size_t i = 0; i < 52; i++)
    {
        ndx1 = rand() % 52;
        ndx2 = rand() % 52;

        Card temp = _cards[ndx1];
        _cards[ndx1] = _cards[ndx2];
        _cards[ndx2] = temp;
    }
}

void WarGame::LoadCards(std::string fileName)
{

    std::ifstream ifs(fileName); // input file stream
    std::string line;
    if (ifs.is_open())
    {
        char delimiter = '>';

        std::string cardLine;
        std::string face;
        std::string suit;
        while (std::getline(ifs, cardLine))
        {
            std::stringstream cardStream(cardLine);
            std::getline(cardStream, face, delimiter);
            std::getline(cardStream, suit, delimiter);
            Card newCard(suit, face);
            _cards.push_back(newCard);
        }
    }
    else
        std::cout << "The cards file could not be opened.\n";
}

void WarGame::ShowCards()
{
    for (auto& card : _cards)
    {
        card.Print();
        std::cout << "\n";
    }
}

void WarGame::PlayGame(std::string playerName, std::string fileName, std::vector<HighScore>& highScores)
{
    bool playAgain = true;
    do
    {
        Shuffle();

        Player player, npc;
        npc.SetName("NPC");
        player.SetName(playerName);

        size_t mid = _cards.size() / 2;
        for (size_t i = 0; i < _cards.size(); i++)
        {
            if (i < mid) player.PushCard(_cards[i]);
            else npc.PushCard(_cards[i]);
        }

        std::vector<Card> unclaimedPile;
        while (player.HasCards())
        {
            Card playerCard = player.PopCard();
            Card npcCard = npc.PopCard();
            playerCard.Print();
            std::cout << " vs. ";
            npcCard.Print();

            unclaimedPile.push_back(playerCard);
            unclaimedPile.push_back(npcCard);
            int compResult = playerCard.Compare(npcCard);
            if (compResult > 0)
            {
                std::cout << " " << player.GetName() << " wins!\n";
                player.WonCards(unclaimedPile);
                unclaimedPile.clear();
            }
            else if (compResult < 0)
            {
                std::cout << " NPC wins!\n";
                npc.WonCards(unclaimedPile);
                unclaimedPile.clear();
            }
            else
                std::cout << std::endl;
        }
        int playerScore = player.GetScore();
        int npcScore = npc.GetScore();
        if (playerScore > npcScore)
        {
            std::cout << " " << player.GetName() << " WINS!  " << playerScore << " to " << npcScore << std::endl;

            if (playerScore > highScores[highScores.size() - 1].score())
            {
                Console::WriteLine( "_#_#_  NEW HIGH SCORE  _#_#_\n", ConsoleColor::Green);
                HighScore hs(player.GetName(), playerScore);
                for (size_t i = 0; i < highScores.size(); i++)
                {
                    if (playerScore >= highScores[i].score())
                    {
                        highScores.insert(highScores.begin() + i, hs);
                        highScores.pop_back();
                        break;
                    }
                }
                //serialize the highScores list
                HighScore::SaveHighScores(fileName, highScores);
                HighScore::ShowHighScores(highScores);
            }
        }
        else if (playerScore < npcScore)
        {
            std::cout << " NPC wins.  " << npcScore << " to " << playerScore << std::endl;
        }
        else
        {
            std::cout << " A TIE! Boo.  " << npcScore << " to " << playerScore << std::endl;
        }

        playAgain = Input::GetInteger("Do you want to play again? (1: Yes, 2: No)", 1, 2) == 1;
    } while (playAgain);
}
