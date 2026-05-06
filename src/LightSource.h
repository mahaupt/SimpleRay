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
#include "Vector3.h"


struct LightSetting {
	double diffuse, specular;

	LightSetting(): 
		diffuse(0), 
		specular(0) 
	{}
};


class LightSource :
	public GameObject
{
protected:
	Color color;
	double intensity;
public:
	LightSource();
	~LightSource();

	virtual LightSetting getLightSetting(Vector3 point, Vector3 normal) { return LightSetting(); }
	virtual Vector3 getDirToLight(Vector3 point) { return position - point; }
	Color getColor() { return color; }
	double getIntensity() { return intensity; }
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Pointlight :
	public LightSource
{
private:
	double falloff;

public:
	Pointlight(Color _color, Vector3 _position, double _intensity, double _falloff);
	virtual LightSetting getLightSetting(Vector3 point, Vector3 normal);
};



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Directionlight :
	public LightSource
{
private:
	Vector3 direction;

public:
	Directionlight(Color _color, Vector3 direction, double intensity);
	virtual LightSetting getLightSetting(Vector3 point, Vector3 normal);
	virtual Vector3 getDirToLight(Vector3 point) { return direction.inverse(); }
};


