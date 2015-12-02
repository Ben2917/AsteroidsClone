

#ifndef OBJECT_H_
#define OBJECT_H_

#include <SDL.h>
#include <SDL_image.h>

#include <memory>
#include <string>
#include <cmath>
#include <vector>

#include "global.h"


class Object;


class GraphicsBase
{


public:


    virtual ~GraphicsBase();


    virtual void Update(Object &obj, SDL_Renderer *ren) = 0;


};


class PhysicsBase
{


public:


    virtual ~PhysicsBase();


    virtual void Update(Object &obj, float frameTime) = 0;


};


class ControlBase
{


public:


    virtual ~ControlBase();


    virtual void Update(Object &obj) = 0;


};


class GraphicsPlayer : public GraphicsBase
{


public:


	GraphicsPlayer(SDL_Renderer* ren, std::string fileName);


	virtual ~GraphicsPlayer();


	virtual void Update(Object &obj, SDL_Renderer* ren);


private:


	std::unique_ptr<SDL_Texture, void(*)(SDL_Texture *)> tex;


};


class PhysicsPlayer : public PhysicsBase
{


public:


    PhysicsPlayer();


    virtual ~PhysicsPlayer();


    virtual void Update(Object &obj, float frameTime);


private:


	


};


class ControlPlayer : public ControlBase
{


public:


	ControlPlayer();


	virtual ~ControlPlayer();


	virtual void Update(Object &obj);


};


class ControlBullet : public ControlBase
{


public:


    ControlBullet(double angle, int speed);


    virtual ~ControlBullet();


    virtual void Update(Object &obj);


private:


    double angle;


    int speed;


};


class Object
{


public:


    Object(SDL_Rect dest, GraphicsBase *gb, 
      PhysicsBase *pb, ControlBase *cb);


    ~Object();


    void Update(SDL_Renderer *ren, float frameTime);


    SDL_Rect dest; // location of the object


    double angle;


    bool addBullet;


    int speed;


    std::vector<Object *> b;


private:


    // change to base class unique ptrs
    std::unique_ptr<GraphicsBase> g;


    std::unique_ptr<PhysicsBase> p;


    std::unique_ptr<ControlBase> c;


};


#endif // OBJECT_H_
