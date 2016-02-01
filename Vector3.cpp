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

#include "Vector3.h"



Vector3::Vector3(double _x, double _y, double _z) {
	x = _x;
	y = _y;
	z = _z;
}


Vector3::Vector3(const Vector3 & vector) {
	x = vector.getX();
	y = vector.getY();
	z = vector.getZ();
}



Vector3 Vector3::operator+ (const Vector3 & vector) const {
	return Vector3(x + vector.getX(), y + vector.getY(), z + vector.getZ());
}

Vector3 Vector3::operator- (const Vector3 & vector) const {
	return Vector3(x - vector.getX(), y - vector.getY(), z - vector.getZ());
}

Vector3 Vector3::operator* (const Vector3 & vector) const {
	return Vector3(y*vector.getZ() - z*vector.getY(), z*vector.getX() - x*vector.getZ(), x*vector.getY() - y*vector.getX());
}

Vector3 Vector3::operator* (double scalar) const {
	return Vector3(x*scalar, y*scalar, z*scalar);
}

Vector3 Vector3::operator/ (double scalar) const {
	return Vector3(x/scalar, y/scalar, z/scalar);
}
