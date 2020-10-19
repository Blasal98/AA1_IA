#include "Obstacle.h"

Obstacle::Obstacle() : h(50), w(50), position({100,100})
{
}
Obstacle::~Obstacle() {}

float Obstacle::getH() {
	return h;
}
float Obstacle::getW() {
	return w;
}
Vector2D Obstacle::getPosition() {
	return position;
}
