

#include "object.h"

#include <iostream>


GraphicsBase::~GraphicsBase(){}


PhysicsBase::~PhysicsBase(){}


ControlBase::~ControlBase(){}


GraphicsPlayer::GraphicsPlayer(SDL_Renderer* ren, std::string fileName)
	: tex(IMG_LoadTexture(ren, fileName.c_str()), SDL_DestroyTexture)
{

	

}


GraphicsPlayer::~GraphicsPlayer() {}


void GraphicsPlayer::Update(Object &obj, SDL_Renderer* ren)
{

    SDL_RenderCopyEx(ren, tex.get(), NULL, 
      &obj.dest, obj.angle, NULL, SDL_FLIP_NONE);

}


PhysicsPlayer::PhysicsPlayer() {}


PhysicsPlayer::~PhysicsPlayer() {}


void PhysicsPlayer::Update(Object &obj, float frameTime)
{

    obj.dest.x += sin(obj.angle * PI / 180) * (obj.speed * frameTime);

    obj.dest.y -= cos(obj.angle * PI / 180) * (obj.speed * frameTime);


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


ControlPlayer::ControlPlayer() {}


ControlPlayer::~ControlPlayer() {}


void ControlPlayer::Update(Object &obj)
{

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_SCANCODE_UP])
	{

		// could add gradual acceleration...
		obj.speed = 320;

	}
	if (!keys[SDL_SCANCODE_UP])
	{
		// ...and decceleration
		obj.speed = 0;

	}
	if (keys[SDL_SCANCODE_LEFT])
	{

		// rotate left
		obj.angle -= 3;

		if (obj.angle <= 0)
			obj.angle = 360;

	}
	if (keys[SDL_SCANCODE_RIGHT])
	{
		obj.angle += 3;

		if (obj.angle >= 360)
			obj.angle = 0;

	}

}


Object::Object(SDL_Rect dest, GraphicsBase *gb, 
  PhysicsBase *pb, ControlBase *cb)
  :g(gb), p(pb), c(cb)
{

	this->dest = dest;

	angle = 0.0;

        speed = 0;

}


Object::~Object() {}


void Object::Update(SDL_Renderer *ren, float frameTime)
{

	c.get()->Update(*this);

        // physics component should resolve this	
	// dest.x += sin(angle * PI / 180) * (speed * frameTime);

	// dest.y -= cos(angle * PI / 180) * (speed * frameTime);
	
	p.get()->Update(*this, frameTime);

	g.get()->Update(*this, ren);

}
