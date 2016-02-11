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
	Vector3 normalized() const;
	double magnitude() const;
	double dot(const Vector3 & vec) const;
	Vector3 inverse() const;
};





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



class HitPoint
{
private:
	Vector3 point;
	Vector3 normal;

public:
	HitPoint() {};
	HitPoint(Vector3 _point, Vector3 _normal): point(_point), normal(_normal) {};
	~HitPoint() {};

	Vector3 getPoint() { return point; }
	Vector3 getNormal() { return normal; }
	void setPoint(Vector3 _point) { point = _point; }
	void setNormal(Vector3 _normal) { normal = _normal; }
};



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Ray
{
private:
	Vector3 point;
	Vector3 direction;

public:
	Ray(const Vector3 & point, const Vector3 & direction);
	~Ray();


	//getters and setters
	Vector3 getPoint() const { return point; }
	Vector3 getDirection() const { return direction; }
	void setPoint(Vector3 _point) { point = _point; }
	void setDirection(Vector3 _dir) { direction = _dir; direction.normalize(); }

	double getDistanceToPoint(Vector3 pt) const;
};



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Color
{
private:
	unsigned char r, g, b;
public:
	Color();
	Color(unsigned char _r, unsigned char _g, unsigned char _b);
	~Color();

	//getters and setters
	unsigned char getR() const { return r; }
	unsigned char getG() const { return g; }
	unsigned char getB() const { return b; }
	void setR(unsigned char _r) { r = _r; }
	void setG(unsigned char _g) { g = _g; }
	void setB(unsigned char _b) { b = _b; }


	//operators
	Color operator+ (const Color & vector) const;
	Color operator- (const Color & vector) const;
	Color operator* (double scalar) const;
};