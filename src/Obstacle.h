#pragma once
#include "Vector2D.h"

class Obstacle {
public:
	Obstacle();
	~Obstacle();
	float getH();
	float getW();
	Vector2D getPosition();
private:
	float h,w;
	Vector2D position;

};
