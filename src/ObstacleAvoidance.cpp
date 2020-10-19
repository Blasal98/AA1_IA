#include "ObstacleAvoidance.h"

ObstacleAvoidance::ObstacleAvoidance()
{
}

ObstacleAvoidance::~ObstacleAvoidance()
{
}

void ObstacleAvoidance::applyComplexSteeringForce(Agent *agent, std::vector<Obstacle*> obstacles, float dtime)
{
	for (int i = 0; i < obstacles.size(); i++) {
		
	}
}


//static bool SegmentSegmentIntersection(Vector2D s1_start, Vector2D s1_end, Vector2D s2_start, Vector2D s2_end,
//	bool doIntersectOnPoints = true, Vector2D* intersectionPoint = nullptr)