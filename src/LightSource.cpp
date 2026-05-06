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


#include "LightSource.h"



LightSource::LightSource() :
	color(255, 255, 255),
	intensity(1)
{
}


LightSource::~LightSource()
{
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



Pointlight::Pointlight(Color _color, Vector3 _position, double _intensity, double _falloff) {
	color = _color;
	intensity = _intensity;
	falloff = _falloff;
	position = _position;
}


LightSetting Pointlight::getLightSetting(Vector3 point, Vector3 normal) {
	LightSetting setting = LightSetting();

	Vector3 direction = point - position;
	double distance = direction.magnitude();
	direction.normalize();

	//diffuse
	setting.diffuse = -direction.dot(normal);
	if (setting.diffuse < 0)
		setting.diffuse = 0;

	setting.diffuse /= pow(distance, falloff);
	setting.diffuse *= intensity;

	//specular

	return setting;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



Directionlight::Directionlight(Color _color, Vector3 _direction, double _intensity)
{
	color = _color;
	intensity = _intensity;
	direction = _direction.normalized();
}


LightSetting Directionlight::getLightSetting(Vector3 point, Vector3 normal) {
	LightSetting setting = LightSetting();

	//diffuse
	setting.diffuse = - normal.dot(direction);
	if (setting.diffuse < 0)
		setting.diffuse = 0;

	setting.diffuse *= intensity;

	//specular

	return setting;
}
