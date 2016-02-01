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

#include "Sphere.h"



Sphere::Sphere(Vector3 _position, double _radius)
{
	position = _position;
	radius = _radius;
}


Sphere::~Sphere()
{
}



bool Sphere::rayCast(const Ray & ray, HitPoint & hit) const {
	double distance = ray.getDistanceToPoint(position);

	if (distance <= radius) {
		
		//calculate hitpoint
		double objectdistance = (ray.getPoint() - position).magnitude();
		double dtp = sqrt(pow(objectdistance, 2) - pow(distance, 2)) - sqrt(pow(radius, 2) - pow(distance, 2));
		Vector3 hitpoint = ray.getPoint() + ray.getDirection()*dtp;
		Vector3 normal = hitpoint - position;
		normal.normalize();

		hit = HitPoint(hitpoint, normal);
		return true;
	}
	return false;
}
