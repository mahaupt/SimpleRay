#pragma once
#include "GameObject.h"

class Sphere :
	public GameObject
{
private:
	double radius;
public:
	Sphere();
	~Sphere();
};

