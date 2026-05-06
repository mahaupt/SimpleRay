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

#pragma once
#include <vector>
#include "Vector3.h"
#include "GameObject.h"
#include "LightSource.h"
#include "Camera.h"
#include "Sphere.h"

class Scene
{
private:
	static Scene* instance;
	std::vector<GameObject*> gameObjects;
	std::vector<LightSource*> lightSources;

public:
	Scene();
	~Scene();

	Sphere & createSphere(double radius, Vector3 position);
	Camera & createCamera(Vector3 position);
	void createLightSource(LightSource * lightsource);
	

	//sets and gets
	std::vector<GameObject*>* getGameObjects() {
		return &gameObjects;
	}
	std::vector<LightSource*>* getLightSources() {
		return &lightSources;
	}

	static Scene* getInstance() { return instance; }
};

