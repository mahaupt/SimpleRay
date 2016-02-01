// Copyright 2016 Marcel Haupt
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http ://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "Scene.h"


Scene* Scene::instance;

Scene::Scene()
{
	instance = this;
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




Sphere &  Scene::createSphere(double radius, Vector3 position) {
	Sphere * sphere = new Sphere(position, radius);
	gameObjects.push_back(sphere);

	return (*sphere);
}



Camera & Scene::createCamera(Vector3 position) {
	Camera * camera = new Camera(position, 1024, 768, 1);
	gameObjects.push_back(camera);

	return (*camera);
}
