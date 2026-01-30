#pragma once
#include <SDL.h>
class GraphicsObject
{
public:
	static void SetRenderer(SDL_Renderer* renderer);
	static SDL_Renderer* GetRenderer();
	static void GetDimensions(int& width, int& height);

	static void Plot(int x, int y);
	static void SetRenderColor(SDL_Color color);

protected:
	static SDL_Renderer* _renderer;
};

