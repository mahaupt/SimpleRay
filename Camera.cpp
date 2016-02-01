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

#include "Camera.h"



Camera::Camera(Vector3 _position, int _width, int _height, double _aof)
{
	position = _position;
	width = _width;
	height = _height;
	aof = _aof;
}


Camera::~Camera()
{
}



void Camera::renderToImage(std::string file) {
	bitmap_image bitmap(width, height);

	double widestside = (width > height) ? width : height;

	//create rays
	for (unsigned int x = 0; x < width; ++x)
	{
		for (unsigned int y = 0; y < height; ++y)
		{
			//calculate ray angles
			double rayanglex = -aof/width*(y- (double)height*0.5);
			double rayangley = aof*(x / (double)width - 0.5);

			//calculate ray direction from angles
			Vector3 direction = Vector3(tan(rayanglex), tan(rayangley), 1);
			Ray ray = Ray(position, direction);

			//start raytracer and get color
			RayTracer rt = RayTracer(ray);
			rt.startRay();
			Color color = rt.getColor();

			//set pixel color
			bitmap.set_pixel(x, y, color.getR(), color.getG(), color.getB());
		}
	}

	bitmap.save_image(file);
}
