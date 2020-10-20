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
	void Pursue(Agent *agent, std::vector<Agent*> agents, int index, float dtime) {
		float T = (agents[index]->getPosition() - agents[0]->getPosition()).Length() / agents[index]->getMaxVelocity();
		Vector2D predictedTarget = agents[0]->getPosition() + agents[0]->getVelocity() * T * 0.5;
		agents[index]->setTarget(predictedTarget);
		SteeringBehaviours::Seek(agents[index], dtime);
	}


	bool ObstacleAvoidance(Agent *agent, std::vector<Obstacle*> obstacles, float dtime)
	{
		Vector2D* intersectionPoint = new Vector2D{ 0,0 };
		bool doesItIntersect = true;
		Vector2D rayCast = agent->getPosition();
		rayCast += agent->getVelocity().Normalize() * 100;
		Vector2D normal = { 0,0 };

		for (int i = 0; i < obstacles.size(); i++) {

			if (Vector2DUtils::SegmentSegmentIntersection(obstacles[i]->getCorners()[0], obstacles[i]->getCorners()[1], //UP
				agent->getPosition(), rayCast,
				doesItIntersect, intersectionPoint)) {
				normal = { 0,-1 };
				break;
			}
			if (Vector2DUtils::SegmentSegmentIntersection(obstacles[i]->getCorners()[2], obstacles[i]->getCorners()[3], //DOWN
				agent->getPosition(), rayCast,
				doesItIntersect, intersectionPoint)) {
				normal = { 0, 1 };
				break;
			}
			if (Vector2DUtils::SegmentSegmentIntersection(obstacles[i]->getCorners()[0], obstacles[i]->getCorners()[2], //LEFT
				agent->getPosition(), rayCast,
				doesItIntersect, intersectionPoint)) {
				normal = { -1, 0 };
				break;
			}
			if (Vector2DUtils::SegmentSegmentIntersection(obstacles[i]->getCorners()[1], obstacles[i]->getCorners()[3], //RIGHT
				agent->getPosition(), rayCast,
				doesItIntersect, intersectionPoint)) {
				normal = { 1, 0 };
				break;
			}
				
		}
		if (normal.x != 0 || normal.y != 0) {

			agent->setTarget(*intersectionPoint + normal * 20);
			SteeringBehaviours::Seek(agent, dtime);

			return true;
		}
		return false;
	}


}