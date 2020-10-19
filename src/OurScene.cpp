#include "OurScene.h"
#include "Seek.h"

using namespace std;

OurScene::OurScene()
{
	//creacio del agent main
	Agent *agent = new Agent;
	agent->setBehavior(new Seek);
	agent->setPosition(Vector2D(1000, 600));
	agent->setTarget(Vector2D(1000, 600));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	mouseTarget = Vector2D(1000, 600);

	//creacio dels agents perseguidors
	maxPursuers = 10;
	for (int i = 0; i < maxPursuers; i++) {
		agent = new Agent;
		agent->setBehavior(new Seek);
		agent->setPosition(Vector2D(20 * i, 20 * i));
		agent->setTarget(Vector2D(20 * i, 20 * i));
		agent->loadSpriteTexture("../res/zombie1.png", 8);
		agent->setComplex(true);

		agents.push_back(agent);
		//target = Vector2D(10 * i, 10 * i);
		
		
	}


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
	agents[0]->update(dtime, event);

	//Pursue
	for (int i = 0; i < maxPursuers; i++) {
		float T = (agents[i + 1]->getPosition() - agents[0]->getPosition()).Length() / agents[i+1]->getMaxVelocity();
		Vector2D predictedTarget = agents[0]->getPosition() + agents[0]->getVelocity() * T * 0.5;
		std::cout << T <<std::endl;
		agents[i+1]->setTarget(predictedTarget);
		agents[i+1]->update(dtime, event);
	}
	
}

void OurScene::draw()
{

	draw_circle(TheApp::Instance()->getRenderer(), (int)mouseTarget.x, (int)mouseTarget.y, 15, 255, 0, 0, 255);
	agents[0]->draw();
	for (int i = 0; i < maxPursuers; i++) {
		agents[i+1]->draw();
		draw_circle(TheApp::Instance()->getRenderer(), agents[i + 1]->getTarget().x, agents[i + 1]->getTarget().y, 15, 0, 255, 0, 255);
	}
}

const char* OurScene::getTitle()
{
	return "SDL Steering Behaviors :: Our Scene";
}