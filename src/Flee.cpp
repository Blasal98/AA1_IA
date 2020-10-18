#include "Flee.h"

Flee::Flee()
{
}

Flee::~Flee()
{
}

void Flee::applySteeringForce(Agent *agent, float dtime)
{
	Vector2D steering = (agent->getTarget() - agent->getPosition())*-1.0f;
	steering.Normalize();
	agent->setVelocity(steering * agent->getMaxVelocity());
	agent->setPosition(agent->getPosition() + agent->getVelocity() * dtime);
}
