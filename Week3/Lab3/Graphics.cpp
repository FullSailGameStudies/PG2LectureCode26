#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <vector>
#include "GraphicsObject.h"
#include <iostream>
#include "Tester.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void ClearScreen(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

//
// TODO: Part A-1: Point2D struct
// TODO: Part A-2: Pixel class
// TODO: Part B-1: Shape class
// TODO: Part B-2.1: Line class
// TODO: Part B-3.1: Triangle class
// TODO: Part B-4.1: Rectangle class
// TODO: Part B-5.1: Circle class
// TODO: Part C-1: ShapeFactory class
//


int main(int argc, char* args[])
{
	Tester tests;
	srand(static_cast<unsigned int>(time(NULL)));

	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//
		// Show menu in console window
		//
		int menuSelection = 0;
		std::vector<std::string> menuOptions{ "1. Draw Pixels", "2. Draw Lines", "3. Draw Triangles", "4. Draw Rectangles", "5. Draw Circles", "6. Draw All", "7. Exit" };
		for (auto& option : menuOptions)
		{
			std::cout << option << "\n";
		}
		std::cout << "\nEnter a number to draw the shapes.\n";


		//Create window
		window = SDL_CreateWindow("Lab 3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
			ClearScreen(renderer);

			GraphicsObject::SetRenderer(renderer);


			SDL_Event e; bool quit = false;
			int width = 0, height = 0;

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
					{
						quit = true;
					}
					else if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED)
					{
						ClearScreen(renderer);
						SDL_RenderPresent(renderer);
					}
					else if (e.type == SDL_KEYUP && e.key.repeat == 0)
					{
						GraphicsObject::GetDimensions(width, height);

						switch (e.key.keysym.sym)
						{
						case SDLK_1:
						{
							ClearScreen(renderer);

							//
							// TODO: Part A-3: Draw Pixels
							//

							//show what's been drawn
							SDL_RenderPresent(renderer);
							break;
						}
						case SDLK_2:
						{
							ClearScreen(renderer);

							//
							// TODO: Part B-2.2: Draw Lines
							//

							//show what's been drawn
							SDL_RenderPresent(renderer);
							break;
						}
						case SDLK_3:
						{
							ClearScreen(renderer);

							//
							// TODO: Part B-3.2: Draw Triangles
							//

							//show what's been drawn
							SDL_RenderPresent(renderer);
							break;
						}
						case SDLK_4:
						{
							ClearScreen(renderer);

							//
							// TODO: Part B-4.2: Draw Rectangles
							//

							//show what's been drawn
							SDL_RenderPresent(renderer);
							break;
						}
						case SDLK_5:
						{
							ClearScreen(renderer);

							//
							// TODO: Part B-5.2: Draw Circles
							//

							//show what's been drawn
							SDL_RenderPresent(renderer);
							break;
						}
						case SDLK_6:
						{
							ClearScreen(renderer);

							//
							// TODO: Part C-2: Random Shapes
							//

							//show what's been drawn
							SDL_RenderPresent(renderer);
							break;
						}

						case SDLK_7: //exit
						{
							quit = true;
							break;
						}
						default:
							break;
						}
					}
				}
			}

			SDL_DestroyRenderer(renderer);

		}
	}

	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}