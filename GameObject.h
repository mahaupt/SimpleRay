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
#include "Vector3.h"
#include "Quaternion.h"

class GameObject
{
protected:
	Vector3 position;
	Vector3 scale;
	Quaternion rotation;

public:
	GameObject();
	GameObject(Vector3 _position);
	~GameObject();

	//getters and setters
	const Vector3 & getPosition() const { return position; }
	void setPosition(Vector3 _position) { position = _position; }
};

