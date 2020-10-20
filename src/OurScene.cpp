#include "OurScene.h"
#include "SteeringBehaviours.h"

using namespace std;

OurScene::OurScene()
{
	//creacio del agent main
	Agent *agent = new Agent;

	agent->setPosition(Vector2D(1000, 600));
	agent->setTarget(Vector2D(1000, 600));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	mouseTarget = Vector2D(1000, 600);

	//creacio dels agents perseguidors
	maxPursuers = 1;
	for (int i = 0; i < maxPursuers; i++) {
		agent = new Agent;

		agent->setPosition(Vector2D(20 * i, 20 * i));
		agent->setTarget(Vector2D(20 * i, 20 * i));
		agent->loadSpriteTexture("../res/zombie1.png", 8);
		//agent->setComplex(true);

		agents.push_back(agent);
		//target = Vector2D(10 * i, 10 * i);
		
		
	}
	obstacles.push_back(new Obstacle());


}

OurScene::~OurScene()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void OurScene::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			mouseTarget = Vector2D((float)(event->button.x), (float)(event->button.y));
			agents[0]->setTarget(mouseTarget);
		}
		break;
	default:
		break;
	}
	for (int i = 0; i < maxPursuers+1; i++) {
		agents[i]->setForce({ 0,0 });

	}

	SteeringBehaviours::Seek(agents[0], dtime);
	agents[0]->update(dtime, event);
	

	for (int i = 0; i < maxPursuers; i++) {
		//Collision
		if (!SteeringBehaviours::ObstacleAvoidance(agents[i + 1], obstacles, dtime)) {
			//Pursue
			SteeringBehaviours::Pursue(agents[i + 1], agents, i + 1, dtime);
		}

	}
	for (int i = 0; i < maxPursuers; i++) agents[i + 1]->update(dtime, event);
	
}

void OurScene::draw()
{

	draw_circle(TheApp::Instance()->getRenderer(), (int)mouseTarget.x, (int)mouseTarget.y, 15, 255, 0, 0, 255);
	agents[0]->draw();
	for (int i = 0; i < maxPursuers; i++) {
		agents[i+1]->draw();
		draw_circle(TheApp::Instance()->getRenderer(), agents[i + 1]->getTarget().x, agents[i + 1]->getTarget().y, 15, 0, 255, 0, 255);
	}
	draw_circle(TheApp::Instance()->getRenderer(), obstacles[0]->getPosition().x, obstacles[0]->getPosition().y, 10, 0, 0, 255, 255);
	draw_circle(TheApp::Instance()->getRenderer(), obstacles[0]->getPosition().x + obstacles[0]->getW(), obstacles[0]->getPosition().y + obstacles[0]->getH(), 10, 0, 0, 255, 255);

	Vector2D auxVector = agents[1]->getPosition() + agents[1]->getVelocity().Normalize()*100;
	draw_circle(TheApp::Instance()->getRenderer(), auxVector.x, auxVector.y, 10, 0, 255, 255, 255);
}

const char* OurScene::getTitle()
{
	return "SDL Steering Behaviors :: Our Scene";
}