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
#include <cmath>

class Vector3
{
private:
	double x, y, z;

public:
	Vector3() :x(0),y(0),z(0){};
	~Vector3() {};

	//initialization functions
	Vector3(double x, double y, double z);
	Vector3(const Vector3 & vector);

	//getters and setters
	double getX() const { return x; }
	double getY() const { return y; }
	double getZ() const { return z; }
	void setX(double _x) { x = _x; }
	void setY(double _y) { y = _y; }
	void setZ(double _z) { z = _z; }

	//operators
	Vector3 operator+ (const Vector3 & vector) const;
	Vector3 operator- (const Vector3 & vector) const;
	Vector3 operator* (const Vector3 & vector) const;
	Vector3 operator* (double scalar) const;
	Vector3 operator/ (double scalar) const;

	void normalize();
	Vector3 & normalized() const;
	double magnitude() const;
	double dot(const Vector3 & vec) const;
};

