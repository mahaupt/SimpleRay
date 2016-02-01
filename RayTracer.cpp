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


bool RayTracer::calculateHitpoint()
{
	HitPoint hp;
	double lastdist = 999999999;
	bool hitted = false;

	//get closest ray target
	std::vector<GameObject*> * gameObjects = Scene::getInstance()->getGameObjects();
	for (std::vector<GameObject*>::iterator it = gameObjects->begin(); it != gameObjects->end(); it++) {
		if ((*it)->rayCast(ray, hp)) {
			hitted = true;

			//save closest hitpoint
			double dist = (ray.getPoint() - hp.getPoint()).magnitude();
			if (dist < lastdist) {
				hitpoint = hp;
				hittingObject = (*it);
				lastdist = dist;
			}
		}
	}

	return hitted;
}



bool RayTracer::startRay() 
{
	//get game object
	if (!calculateHitpoint()) {
		return false;
	}

	//hitted game object - get color
	Color ambient = Color(20, 20, 20);
	Color material = Color(200, 100, 100);
	

	Vector3 lightdir = Vector3(1, -1, -1);
	lightdir.normalize();

	double matfac = hitpoint.getNornal().dot(lightdir);
	if (matfac < 0) matfac = 0;

	color = ambient + material * matfac;

	return true;
}
