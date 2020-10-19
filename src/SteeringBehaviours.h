#include "Agent.h"

namespace SteeringBehaviours {
	void Seek(Agent *agent, float dtime)
	{
		/*Vector2D steering = agent->getTarget() - agent->getPosition();
		steering.Normalize();
		agent->setVelocity (steering * agent->getMaxVelocity());
		agent->setPosition (agent->getPosition() + agent->getVelocity() * dtime);*/

		Vector2D desiredVelocity = agent->getTarget() - agent->getPosition();
		desiredVelocity.Normalize();
		desiredVelocity *= agent->getMaxVelocity();
		Vector2D steeringForce = desiredVelocity - agent->getVelocity();
		steeringForce /= agent->getMaxVelocity();
		agent->addForce(steeringForce * agent->getMaxForce());

	}
	void ObstacleAvoidance(Agent *agent, std::vector<Obstacle*> obstacles, float dtime)
	{
		Vector2D* intersectionPoint = new Vector2D{ 0,0 };
		bool doesItIntersect = false;
		Vector2D rayCast = agent->getPosition();
		rayCast += agent->getVelocity().Normalize() /** lookAhead*/;

		for (int i = 0; i < obstacles.size(); i++) {

			Vector2DUtils::SegmentSegmentIntersection(obstacles[i]->getCorners()[0], obstacles[i]->getCorners()[1],
				agent->getPosition(), rayCast,
				doesItIntersect, intersectionPoint);
		}
	}


}