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
		std::vector<Vector2D> intersectionPoints;
		std::vector<Vector2D> intersectionNormals;

		for (int i = 0; i < obstacles.size(); i++) {

			if (Vector2DUtils::SegmentSegmentIntersection(obstacles[i]->getCorners()[0], obstacles[i]->getCorners()[1], //UP
				agent->getPosition(), rayCast,
				doesItIntersect, intersectionPoint)) {
				intersectionPoints.push_back(*intersectionPoint);
				normal = { 0,-1 };
				intersectionNormals.push_back(normal);


			}
			if (Vector2DUtils::SegmentSegmentIntersection(obstacles[i]->getCorners()[2], obstacles[i]->getCorners()[3], //DOWN
				agent->getPosition(), rayCast,
				doesItIntersect, intersectionPoint)) {
				intersectionPoints.push_back(*intersectionPoint);
				normal = { 0, 1 };
				intersectionNormals.push_back(normal);


			}
			if (Vector2DUtils::SegmentSegmentIntersection(obstacles[i]->getCorners()[0], obstacles[i]->getCorners()[2], //LEFT
				agent->getPosition(), rayCast,
				doesItIntersect, intersectionPoint)) {
				intersectionPoints.push_back(*intersectionPoint);
				normal = { -1, 0 };
				intersectionNormals.push_back(normal);


			}
			if (Vector2DUtils::SegmentSegmentIntersection(obstacles[i]->getCorners()[1], obstacles[i]->getCorners()[3], //RIGHT
				agent->getPosition(), rayCast,
				doesItIntersect, intersectionPoint)) {
				intersectionPoints.push_back(*intersectionPoint);
				normal = { 1, 0 };
				intersectionNormals.push_back(normal);


			}
			
		}
		int nearestPointIndex = -1;
		if (intersectionPoints.size() > 0) {
			nearestPointIndex = 0;

			for (int i = 1; i < intersectionPoints.size(); i++) {
				if ((agent->getPosition() - intersectionPoints[nearestPointIndex]).Length() > (agent->getPosition() - intersectionPoints[i]).Length()) {
					nearestPointIndex = i;
				}
			}
		}
			

		if (nearestPointIndex >= 0) {

			agent->setTarget(intersectionPoints[nearestPointIndex] + intersectionNormals[nearestPointIndex] * 20);
			SteeringBehaviours::Seek(agent, dtime);

			return true;
		}
		return false;
	}

	

	void CalculateSeparationDirection(Agent *agent, std::vector<Agent*> agents, int agent_index, Vector2D* separationDir, float r)
	{
		Vector2D separationVec = {0,0};
		int neighbourCount = 0;

		for (int i = 1; i < agents.size(); i++)
		{
			if (i != agent_index) {
				if ((agent->getPosition() - agents[i]->getPosition()).Length() <= r) {
					separationVec += (agent->getPosition() - agents[i]->getPosition());
					neighbourCount++;
				}
			}

		}
		separationVec /= neighbourCount;
		*separationDir = separationVec.Normalize();
	}

	void CalculateCohesionDirection(Agent *agent, std::vector<Agent*> agents, int agent_index, Vector2D* cohesionDir, float r)
	{
		Vector2D averagePosition = { 0,0 };
		int neighbourCount = 0;

		for (int i = 1; i < agents.size(); i++)
		{
			if (i != agent_index) {
				if ((agent->getPosition() - agents[i]->getPosition()).Length() <= r) {
					averagePosition += (agents[i]->getPosition());
					neighbourCount++;
				}
			}

		}
		averagePosition /= neighbourCount;
		averagePosition -= agent->getPosition();
		*cohesionDir = averagePosition.Normalize();
	}

	void CalculateAlignmentDirection(Agent *agent, std::vector<Agent*> agents, int agent_index, Vector2D* alignmentDir, float r)
	{
		Vector2D averageVelocity = { 0,0 };
		int neighbourCount = 0;

		for (int i = 1; i < agents.size(); i++)
		{
			if (i != agent_index) {
				if ((agent->getPosition() - agents[i]->getPosition()).Length() <= r) {
					averageVelocity += (agents[i]->getVelocity());
					neighbourCount++;
				}
			}

		}
		averageVelocity /= neighbourCount;
		*alignmentDir = averageVelocity.Normalize();
	}

	void Flocking(Agent *agent, std::vector<Agent*> agents, int agent_index, float dtime)
	{
		float K_SEPARATION_FORCE = 1;
		float K_COHESION_FORCE = 1;
		float K_ALIGNMENT_FORCE = 1;
		float radius = 50;

		Vector2D* separationDir = new Vector2D;
		Vector2D* cohesionDir = new Vector2D;
		Vector2D* alignmentDir = new Vector2D;
		CalculateSeparationDirection(agent, agents, agent_index, separationDir, radius);
		CalculateCohesionDirection(agent, agents, agent_index, cohesionDir, radius);
		CalculateAlignmentDirection(agent, agents, agent_index, alignmentDir, radius);
		Vector2D FlockingForce = *separationDir * K_SEPARATION_FORCE + *cohesionDir * K_COHESION_FORCE + *alignmentDir * K_ALIGNMENT_FORCE;
		FlockingForce.Normalize();
		agent->addForce(FlockingForce * agent->getMaxForce()*0.5);
	}
}