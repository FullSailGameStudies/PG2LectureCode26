#include "GraphicsObject.h"

SDL_Renderer* GraphicsObject::_renderer = nullptr;


void GraphicsObject::SetRenderer(SDL_Renderer* renderer)
{
	_renderer = renderer;
}


SDL_Renderer* GraphicsObject::GetRenderer()
{
	return _renderer;
}

void GraphicsObject::GetDimensions(int& width, int& height)
{
	SDL_GetRendererOutputSize(_renderer, &width, &height);
}


void GraphicsObject::Plot(int x, int y)
{
	SDL_RenderDrawPoint(_renderer, x, y);
}

void GraphicsObject::SetRenderColor(SDL_Color color)
{
	SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
}
