#include <Console.h>
#include "MatchingGame.h"
#include "Tester.h"

//Screen dimension constants
const int SCREEN_WIDTH = 750;
const int SCREEN_HEIGHT = 750;

int main(int argc, char* args[])
{
	Tester tests;

	PG2Graphics engine(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!engine.Init())
	{
		printf("Failed to initialize Graphics Engine!\n");
	}
	else
	{
		MatchingGame game;
		game.Run(engine);
	}
	engine.Close();
	return 0;
}