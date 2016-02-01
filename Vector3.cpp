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
