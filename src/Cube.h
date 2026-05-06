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

class Cube : public GameObject {
 private:
  double size;

 public:
  Cube(Vector3 position, double size);
  ~Cube();

  double getSize() const { return size; }
  void setSize(double _size) { size = _size; }
  virtual bool rayCast(const Ray& ray, HitPoint& hit) const;
};
