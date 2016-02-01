#pragma once
#include "Vector3.h"

class GameObject
{
protected:
	Vector3 position;
public:
	GameObject();
	GameObject(Vector3 _position);
	~GameObject();

	//getters and setters
	const Vector3 & getPosition() const { return position; }
	void setPosition(Vector3 _position) { position = _position; }
};

