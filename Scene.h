#pragma once
#include <vector>
#include "Vector3.h"
#include "GameObject.h"

class Scene
{
private:
	std::vector<GameObject*> gameObjects;

public:
	Scene();
	~Scene();


	void createSphere(double radius, Vector3 position);
};

