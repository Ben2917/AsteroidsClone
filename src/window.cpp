

#include "window.h"


RenderWindow::RenderWindow(int x, int y, int w, int h) :
	win(SDL_CreateWindow("RenderWindow", x, y, w, h, SDL_WINDOW_SHOWN),
		SDL_DestroyWindow),
	ren(SDL_CreateRenderer(win.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
		SDL_DestroyRenderer)
{



}


RenderWindow::~RenderWindow() {}


SDL_Window *RenderWindow::GetWindow()
{

	return win.get();

}


SDL_Renderer *RenderWindow::GetRenderer()
{

	return ren.get();

}


void RenderWindow::ClearRenderer()
{

	SDL_RenderClear(ren.get());

}


void RenderWindow::PresentRenderer()
{

	SDL_RenderPresent(ren.get());

}