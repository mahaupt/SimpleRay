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

	/*for (unsigned int x = 0; x < width; ++x)
	{
		for (unsigned int y = 0; y < height; ++y)
		{
			rgb_store col = jet_colormap[(y) % height];
			bitmap.set_pixel(x, y, col.red, col.green, col.blue);
		}
	}*/

	bitmap.save_image(file);
}
