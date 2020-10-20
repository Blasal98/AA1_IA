#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"

class OurScene :
	public Scene
{
public:
	OurScene();
	~OurScene();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	std::vector<Obstacle*> obstacles;
	Vector2D mouseTarget;
	int maxPursuers;
}; 
