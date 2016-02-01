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
#include "Ray.h"
#include "Color.h"
#include "GameObject.h"

class RayTracer
{
private:
	Ray ray;
	Color color;

	GameObject * getNearestHittingObject();
public:
	RayTracer(Ray _ray);
	~RayTracer();

	bool startRay();
	Color getColor() { return color; }
};

