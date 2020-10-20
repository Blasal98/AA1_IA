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
	bool ObstacleAvoidance(Agent *agent, std::vector<Obstacle*> obstacles, float dtime)
	{
		Vector2D* intersectionPoint = new Vector2D{ 0,0 };
		bool doesItIntersect = false;
		Vector2D rayCast = agent->getPosition();
		rayCast += agent->getVelocity().Normalize() * 100;

		for (int i = 0; i < obstacles.size(); i++) {

			if (Vector2DUtils::SegmentSegmentIntersection(obstacles[i]->getCorners()[0], obstacles[i]->getCorners()[1],
				agent->getPosition(), rayCast,
				doesItIntersect, intersectionPoint))
				break;
		}
		return doesItIntersect;
	}
	
	void Flocking(Agent *agent, std::vector<Agent> agents, int agent_index, float dtime)
	{
		Vector2D separationDir;
		Vector2D cohesionDir;
		Vector2D alignmentDir;
		CalculateSeparationDirection(agents, agent_index, separationDir);
		CalculateCohesionDirection(agents, agent_index, cohesionDir);
		CalculateAlignmentDirection(agents, agent_index, alignmentDir);
		Vector2D FlockingForce = separationDir * K_SEPARATION_FORCE + cohesionDir * K_COHESION_FORCE + alignmentDir * K_ALIGNMENT_FORCE;
		agent->addForce(FlockingForce);
	}

	void CalculateSeparationDirection(std::vector<Agent> agents, int agent_index, Vector2D separationDir)
	{
		int neighbourCount = agent_index;
		Vector2D separationVec;
		//foreach agent in array no se com posarlo
		for each() 
		{
			if (distance(agents[agent_index].getPosition, position) < NEIGHTBOUR_RADIUS)
			{
				separationVec += (position - agents[agent_index]);
				neighbourCount++;
			}
		}
		separationVec /= neighbourCount;
		separationDir = normalize(separationVec);
	}

	void CalculateCohesionDirection(std::vector<Agent> agents, int agent_index, Vector2D cohesionDir)
	{
		int neighbourCount = agent_index;
		Vector2D cohesionVec;
		//foreach agent in array no se com posarlo
		for each()
		{
			if (distance(agents[agent_index].getPosition, position) < NEIGHTBOUR_RADIUS)
			{
				cohesionVec += (position - agents[agent_index].getPosition);
				neighbourCount++;
			}
		}
		cohesionVec /= neighbourCount;
		cohesionDir = normalize(cohesionVec);
	}

	void CalculateAlignmentDirection(std::vector<Agent> agents, int agent_index, Vector2D alignmentDir)
	{
		int neighbourCount = agent_index;
		Vector2D averageVelocity;
		//foreach agent in array no se com posarlo
		for each()
		{
			if (distance(agents[agent_index].getPosition, position) < NEIGHTBOUR_RADIUS)
			{
				averageVelocity += agents[agent_index].getVelocity;
				neighbourCount++;
			}
		}
		averageVelocity /= neighbourCount;
		alignmentDir = normalize(averageVelocity);
	}
}