#include "Seek.h"

Seek::Seek()
{
}

Seek::~Seek()
{
}

void Seek::applySteeringForce(Agent *agent, float dtime)
{
	Vector2D steering = agent->getTarget() - agent->getPosition();
	steering.Normalize();
	agent->setVelocity (steering * agent->getMaxVelocity());
	agent->setPosition (agent->getPosition() + agent->getVelocity() * dtime);
}
