

#ifndef WINDOW_H_
#define WINDOW_H_


#include <memory>
#include <SDL.h>


class RenderWindow
{


public:


	RenderWindow(int, int, int, int);


	~RenderWindow();


	SDL_Window *GetWindow();


	SDL_Renderer *GetRenderer();


	void ClearRenderer();


	void PresentRenderer();


private:


	std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> win;

	std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> ren;


};


#endif // WINDOW_H_
