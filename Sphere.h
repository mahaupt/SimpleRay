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
#include "GameObject.h"

class Sphere :
	public GameObject
{
private:
	double radius;
public:
	Sphere(Vector3 _position, double radius);
	~Sphere();

	//getters and setters
	double getRadius() const { return radius; }
	void setRadius(double _radius) { radius = _radius; }
};

