#pragma once
#include <iostream>
#include <minmax.h>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_SimpleApp.h"
#include "Vector2D.h"
#include "utils.h"
#include <vector>
#include "Obstacle.h"

class Agent
{

private:
	
	Vector2D position;
	Vector2D velocity;
	Vector2D target;
	Vector2D totalForce;
	float mass;

	float speed;
	float orientation;
	float max_force;
	float max_velocity;

	SDL_Texture *sprite_texture;
	bool draw_sprite;
	int sprite_num_frames;
	int sprite_w;
	int sprite_h;

	int index;
	std::vector<Agent*> gameAgents;

public:
	Agent();
	~Agent();
	Vector2D getPosition();
	Vector2D getTarget();
	Vector2D getVelocity();
	float getMaxVelocity();
	float getMaxForce();

	void setPosition(Vector2D position);
	void setTarget(Vector2D target);
	void setVelocity(Vector2D velocity);
	void update(float dtime, SDL_Event *event);
	void draw();
	bool Agent::loadSpriteTexture(char* filename, int num_frames=1);

	void setGameAgents(std::vector<Agent*> vec);
	void setIndex(int _i);
	void addForce(Vector2D _f);
	void setForce(Vector2D _f);
};
