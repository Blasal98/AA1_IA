#pragma once
#include "Agent.h"

class ObstacleAvoidance :
	public Agent::SteeringBehavior
{
public:
	ObstacleAvoidance();
	~ObstacleAvoidance();
	void applyComplexSteeringForce(Agent *agent, std::vector<Obstacle*> obstacles, float dtime);
private:
	float lookAhead = 10;
};
