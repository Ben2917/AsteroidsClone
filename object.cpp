

#include "object.h"

#include <iostream>


GraphicsComponent::GraphicsComponent(SDL_Renderer* ren, std::string fileName)
	: tex(IMG_LoadTexture(ren, fileName.c_str()), SDL_DestroyTexture)
{

	

}


GraphicsComponent::~GraphicsComponent() {}


void GraphicsComponent::Draw(SDL_Renderer* ren, SDL_Rect dest, double angle)
{

	SDL_RenderCopyEx(ren, tex.get(), NULL, &dest, angle, NULL, SDL_FLIP_NONE);

}


PhysicsComponent::PhysicsComponent() {}


PhysicsComponent::~PhysicsComponent() {}


void PhysicsComponent::ResolveCollision(SDL_Rect dest,
	std::vector<SDL_Rect> screenObjects)
{

	/*

	check world collision

	per-pixel collision?

	for(int i = 0; i < screenObjects.size(); ++i)
	{

	  if(triangle pixel touches screenObjects[i] pixel)
	  {

	    GAME_OVER = true;

	  }

	}
	*/

}


ControlComponent::ControlComponent() {}


ControlComponent::~ControlComponent() {}


void ControlComponent::HandleInput(double *angle, int *speed)
{

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_SCANCODE_UP])
	{

		// could add gradual acceleration...
		*speed = 320;

	}
	if (!keys[SDL_SCANCODE_UP])
	{
		// ...and decceleration
		*speed = 0;

	}
	if (keys[SDL_SCANCODE_LEFT])
	{

		// rotate left
		*angle -= 3;

		if (*angle <= 0)
			*angle = 360;

	}
	if (keys[SDL_SCANCODE_RIGHT])
	{
		*angle += 3;

		if (*angle >= 360)
			*angle = 0;

	}

}


Object::Object(int x, int y, int w, int h, std::string fileName, SDL_Renderer* ren)
	:g(new GraphicsComponent(ren, fileName)),
	p(new PhysicsComponent()),
	c(new ControlComponent())
{

	dest = { x, y, w, h };

	angle = 0.0;

}


Object::~Object() {}


void Object::Update(SDL_Renderer *ren, float frameTime)
{

	c.get()->HandleInput(&angle, &speed);
	
	dest.x += sin(angle * PI / 180) * (speed * frameTime);

	dest.y -= cos(angle * PI / 180) * (speed * frameTime);
	
	// p.get()->ResolveCollision(dest, );

	g.get()->Draw(ren, dest, angle);

}