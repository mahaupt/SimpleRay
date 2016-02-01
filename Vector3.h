#pragma once
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
};

