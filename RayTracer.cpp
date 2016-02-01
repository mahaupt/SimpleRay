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

#include "RayTracer.h"
#include "Scene.h"


RayTracer::RayTracer(Ray _ray) :
	ray(_ray)
{
}


RayTracer::~RayTracer()
{
}


GameObject * RayTracer::getNearestHittingObject()
{
	std::vector<GameObject*> * gameObjects = Scene::getInstance()->getGameObjects();
	Sphere * sphere = (Sphere*)(*gameObjects)[0];

	if (ray.getDistanceToPoint(sphere->getPosition()) <= sphere->getRadius()) {
		return (*gameObjects)[0];
	}
	return 0;
}



bool RayTracer::startRay() 
{
	//get game object
	GameObject * gameObject = getNearestHittingObject();
	if (gameObject == 0) return false;

	//hitted game object - get color
	color = Color(255, 255, 255);
	return true;
}
