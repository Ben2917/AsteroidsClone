

#ifndef OBJECT_H_
#define OBJECT_H_

#include <SDL.h>
#include <SDL_image.h>

#include <memory>
#include <string>
#include <cmath>
#include <vector>

#include "global.h"

class GraphicsComponent
{


public:


	GraphicsComponent(SDL_Renderer* ren, std::string fileName);


	~GraphicsComponent();


	void Draw(SDL_Renderer* ren, SDL_Rect dest, double angle);


private:


	std::unique_ptr<SDL_Texture, void(*)(SDL_Texture *)> tex;


};


class PhysicsComponent
{


public:


	PhysicsComponent();


	~PhysicsComponent();


	void ResolveCollision(SDL_Rect dest, std::vector<SDL_Rect> screenObjects);


private:


	// vector calculation functions


};


class ControlComponent
{


public:


	ControlComponent();


	~ControlComponent();


	void HandleInput(double *angle, int *);


};


class Object
{


public:


	// x, y, w, h, tex_filename
	Object(int, int, int, int, std::string, SDL_Renderer*);


	~Object();


	void Update(SDL_Renderer *, float);


private:


	SDL_Rect dest; // location of the object


	double angle;


	int speed;


	std::unique_ptr<GraphicsComponent> g;


	std::unique_ptr<PhysicsComponent> p;


	std::unique_ptr<ControlComponent> c;


};


#endif // OBJECT_H_
