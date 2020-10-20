#pragma once
#include "Vector2D.h"

class Obstacle {
public:
	Obstacle();
	Obstacle(float _h, float _w, Vector2D _position);
	~Obstacle();
	float getH();
	float getW();
	Vector2D getPosition();
	Vector2D* getCorners();
private:
	float h,w;
	Vector2D position;
	Vector2D* corners;
};
