

#include <iostream>

#include "window.h"
#include "object.h"
#include "timer.h"

#include <SDL.h>


bool GAME_OVER = false;


bool EventLoop()
{

	SDL_Event e;

	while (SDL_PollEvent(&e))
	{

		if (e.type == SDL_QUIT)
		{

			return true;

		}
		else if (e.type == SDL_KEYDOWN
			&& e.key.keysym.sym == SDLK_ESCAPE)
		{

			return true;

		}
		
	}

	return false;

}


void MainLoop()
{

	std::unique_ptr<RenderWindow> myWin(
		new RenderWindow(30, 30, WIN_WIDTH, WIN_HEIGHT));

    std::unique_ptr<Object> player(
      new Object({WIN_WIDTH / 2, WIN_HEIGHT / 2, 64, 64},
      new GraphicsPlayer(myWin->GetRenderer(), "triangle.png"),
      new PhysicsPlayer(), new ControlPlayer()));

	Timer myTimer;

	float frameTime = 0.0;

	while (!EventLoop() || GAME_OVER)
	{

		myTimer.StartTimer();

		SDL_Delay(17);

		myWin.get()->ClearRenderer();

		player.get()->Update(myWin.get()->GetRenderer(), frameTime);
		
		myWin.get()->PresentRenderer();

		myTimer.StopTimer();

		frameTime = myTimer.GetTimeSeconds();

	}

    // print game over and score

}


int main(int argc, char** argv)
{

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{

		return -1;

	}

	MainLoop();

	SDL_Quit();

	return 0;

}
