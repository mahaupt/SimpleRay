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

#include <algorithm>
#include <cmath>
#include <limits>

#include "Cube.h"

namespace {
bool updateSlab(double origin, double direction, double minBound,
                double maxBound, double& tMin, double& tMax) {
  if (std::abs(direction) < 1e-9) {
    return origin >= minBound && origin <= maxBound;
  }

  double t0 = (minBound - origin) / direction;
  double t1 = (maxBound - origin) / direction;
  if (t0 > t1) {
    std::swap(t0, t1);
  }

  tMin = std::max(tMin, t0);
  tMax = std::min(tMax, t1);
  return tMin <= tMax;
}
}

Cube::Cube(Vector3 _position, double _size) {
  position = _position;
  size = _size;
}

Cube::~Cube() {}

bool Cube::rayCast(const Ray& ray, HitPoint& hit) const {
  const double halfSize = size * 0.5;
  const Vector3 minBound(-halfSize, -halfSize, -halfSize);
  const Vector3 maxBound(halfSize, halfSize, halfSize);

  double tMin = -std::numeric_limits<double>::infinity();
  double tMax = std::numeric_limits<double>::infinity();

  const Quaternion inverseRotation = rotation.conjugate().normalized();
  const Vector3 rayOrigin = inverseRotation.rotate(ray.getPoint() - position);
  const Vector3 rayDirection = inverseRotation.rotate(ray.getDirection());

  if (!updateSlab(rayOrigin.getX(), rayDirection.getX(), minBound.getX(),
                  maxBound.getX(), tMin, tMax) ||
      !updateSlab(rayOrigin.getY(), rayDirection.getY(), minBound.getY(),
                  maxBound.getY(), tMin, tMax) ||
      !updateSlab(rayOrigin.getZ(), rayDirection.getZ(), minBound.getZ(),
                  maxBound.getZ(), tMin, tMax)) {
    return false;
  }

  if (tMax < 0) {
    return false;
  }

  const double tHit = tMin >= 0 ? tMin : tMax;
  const Vector3 localHitPoint = rayOrigin + rayDirection * tHit;

  Vector3 normal(0, 0, 0);
  const double epsilon = 1e-6;

  if (std::abs(localHitPoint.getX() - minBound.getX()) < epsilon) {
    normal = Vector3(-1, 0, 0);
  } else if (std::abs(localHitPoint.getX() - maxBound.getX()) < epsilon) {
    normal = Vector3(1, 0, 0);
  } else if (std::abs(localHitPoint.getY() - minBound.getY()) < epsilon) {
    normal = Vector3(0, -1, 0);
  } else if (std::abs(localHitPoint.getY() - maxBound.getY()) < epsilon) {
    normal = Vector3(0, 1, 0);
  } else if (std::abs(localHitPoint.getZ() - minBound.getZ()) < epsilon) {
    normal = Vector3(0, 0, -1);
  } else {
    normal = Vector3(0, 0, 1);
  }

  hit = HitPoint(rotation.rotate(localHitPoint) + position,
                 rotation.rotate(normal));
  return true;
}
