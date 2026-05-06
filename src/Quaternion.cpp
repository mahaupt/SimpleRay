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

#include "Quaternion.h"

Quaternion::Quaternion() {
  x = 0;
  y = 0;
  z = 0;
  w = 1;
}

Quaternion::Quaternion(double _x, double _y, double _z, double _w) {
  x = _x;
  y = _y;
  z = _z;
  w = _w;
}

Quaternion::~Quaternion() {}

Quaternion Quaternion::fromAxisAngle(const Vector3& axis, double angle) {
  Vector3 normalizedAxis = axis.normalized();
  const double halfAngle = angle * 0.5;
  const double sinHalfAngle = sin(halfAngle);

  return Quaternion(normalizedAxis.getX() * sinHalfAngle,
                    normalizedAxis.getY() * sinHalfAngle,
                    normalizedAxis.getZ() * sinHalfAngle, cos(halfAngle));
}

Quaternion Quaternion::conjugate() const {
  return Quaternion(-x, -y, -z, w);
}

Quaternion Quaternion::normalized() const {
  const double magnitude = sqrt(x * x + y * y + z * z + w * w);
  return Quaternion(x / magnitude, y / magnitude, z / magnitude, w / magnitude);
}

Quaternion Quaternion::operator*(const Quaternion& quat) const {
  return Quaternion(w * quat.getX() + x * quat.getW() + y * quat.getZ() -
                        z * quat.getY(),
                    w * quat.getY() - x * quat.getZ() + y * quat.getW() +
                        z * quat.getX(),
                    w * quat.getZ() + x * quat.getY() - y * quat.getX() +
                        z * quat.getW(),
                    w * quat.getW() - x * quat.getX() - y * quat.getY() -
                        z * quat.getZ());
}

Vector3 Quaternion::rotate(const Vector3& vec) const {
  const Quaternion unitQuat = normalized();
  const Quaternion rotated =
      unitQuat * Quaternion(vec.getX(), vec.getY(), vec.getZ(), 0) *
      unitQuat.conjugate();
  return Vector3(rotated.getX(), rotated.getY(), rotated.getZ());
}
