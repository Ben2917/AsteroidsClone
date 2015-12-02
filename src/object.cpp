

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
    if (keys[SDL_SCANCODE_SPACE])
    {

        obj.addBullet = true;    

    }

}


ControlBullet::ControlBullet(double angle, int speed)
{

    this->angle = angle;

    this->speed = speed;

}


ControlBullet::~ControlBullet(){}


void ControlBullet::Update(Object &obj)
{

    obj.angle = angle;

    obj.speed = speed;

}



Object::Object(SDL_Rect dest, GraphicsBase *gb, 
  PhysicsBase *pb, ControlBase *cb)
  :g(gb), p(pb), c(cb)
{

	this->dest = dest;

	angle = 0.0;

        speed = 0;

        addBullet = false;

}


Object::~Object() 
{

    // Delete any remaining bullets
    for(unsigned int i = 0; i < b.size(); ++i)
    {

        delete b[i];

        b[i] = 0;

    }

}


void Object::Update(SDL_Renderer *ren, float frameTime)
{

    c.get()->Update(*this);
	
    p.get()->Update(*this, frameTime);

    // need a bullet handler component
    if(addBullet)
    {

        b.push_back(new Object(
          {dest.x / 2, dest.y / 2, 2, 2}, 
          new GraphicsPlayer(ren, "square.png"), 
          new PhysicsPlayer(), new ControlBullet(angle, speed))); 

        addBullet = false;

    }

    for(unsigned int i = 0; i < b.size(); ++i)
    {

        b[i]->Update(ren, frameTime);

    }

    g.get()->Update(*this, ren);

    // check bullet collision    

}
