#include "Scene.h"



Scene::Scene()
{
	gameObjects = std::vector<GameObject*>();
}



Scene::~Scene()
{
	//destroy all game objects
	for (std::vector<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); it++) {
		if ((*it) != 0) {
			delete (*it);
			(*it) = 0;
		}
	}
	//clear container
	gameObjects.clear();
}




void Scene::createSphere(double radius, Vector3 position) {
	//gameObjects.push_back();
}
