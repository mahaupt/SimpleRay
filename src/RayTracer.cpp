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
	ray(_ray),
	hittingObject(0)
{
}


RayTracer::~RayTracer()
{
}


bool RayTracer::calculateHitpoint(GameObject * ignoredObject, double maxDistance)
{
	HitPoint hp;
	double lastdist = 999999999;
	bool hitted = false;

	//get closest ray target
	std::vector<GameObject*> * gameObjects = Scene::getInstance()->getGameObjects();
	for (std::vector<GameObject*>::iterator it = gameObjects->begin(); it != gameObjects->end(); it++) {
		if ((*it) == ignoredObject) {
			continue;
		}
		if ((*it)->rayCast(ray, hp)) {
			//save closest hitpoint
			double dist = (ray.getPoint() - hp.getPoint()).magnitude();
			if (dist <= 1e-6) {
				continue;
			}
			if (maxDistance > 0 && dist >= maxDistance) {
				continue;
			}
			//double dir = (hp.getPoint() - ray.getPoint()).dot(ray.getDirection()); && dir > 0
			if (dist < lastdist) {
				hitpoint = hp;
				hittingObject = (*it);
				lastdist = dist;
				hitted = true;
			}
		}
	}

	return hitted;
}



bool RayTracer::startRay(GameObject * ignoredObject, double maxDistance) 
{
	//get game object
	if (!calculateHitpoint(ignoredObject, maxDistance)) {
		return false;
	}

	return true;
}


void RayTracer::doLightCalculations() {
	//hitted game object - get color
	Color ambient = Color(20, 10, 10);
	Color diffuse = Color(200, 100, 100);
	double diffuse_light = 0;

	//cycle through lights
	std::vector<LightSource*> * lightSources = Scene::getInstance()->getLightSources();
	for (std::vector<LightSource*>::iterator it = lightSources->begin(); it != lightSources->end(); it++) {

		//shoot ray to light
		Vector3 direction = (*it)->getDirToLight(hitpoint.getPoint());
		Vector3 offsetPoint = hitpoint.getPoint() + hitpoint.getNormal() * 1e-4;
		Ray rtray = Ray(offsetPoint, direction);
		RayTracer rt = RayTracer(rtray); 
		double maxDistance = (*it)->getMaxDistanceFrom(hitpoint.getPoint());

		//on hit - do light calculations
		if (!rt.startRay(hittingObject, maxDistance)) {
			LightSetting ls = (*it)->getLightSetting(hitpoint.getPoint(), hitpoint.getNormal());
			diffuse_light += ls.diffuse;
		}
	}

	color = ambient + diffuse * diffuse_light;
}
