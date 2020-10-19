#include "Obstacle.h"

Obstacle::Obstacle() : h(50), w(50), position({75,100})
{
	corners = new Vector2D[4];

	corners[0] = { position.x,position.y };
	corners[1] = { position.x + w,position.y };
	corners[2] = { position.x,position.y + h };
	corners[3] = { position.x + w,position.y + h };
}
Obstacle::Obstacle(float _h, float _w, Vector2D _position) {
	h = _h;
	w = _w;
	position = _position;
	corners = new Vector2D[4];

	corners[0] = { position.x,position.y };
	corners[1] = { position.x+w,position.y };
	corners[2] = { position.x,position.y+h };
	corners[3] = { position.x+w,position.y+h };


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
Vector2D* Obstacle::getCorners() {
	return corners;
}
