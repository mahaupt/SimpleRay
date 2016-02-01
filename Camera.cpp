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

	unsigned int nthreads = 1;

	//create 4 threads
	std::vector<std::thread> threadlist = std::vector<std::thread>();
	for (int i = 0; i < nthreads; i++) {
		threadlist.push_back(std::thread(renderThread, this, &bitmap, i, nthreads));
	}
	

	//join the threads
	for (std::vector<std::thread>::iterator it = threadlist.begin(); it != threadlist.end(); it++) {
		(*it).join();
	}


	bitmap.save_image(file);
}


void Camera::renderThread(Camera * camera, bitmap_image * bitmap, unsigned int tid, unsigned int threadNumber) {
	//create rays
	for (unsigned int x = tid; x < camera->getWidth(); x+=threadNumber)
	{
		for (unsigned int y = 0; y < camera->getHeight(); ++y)
		{
			//calculate ray angles
			double rayanglex = -camera->getAOF() / camera->getWidth()*(y - (double)camera->getHeight()*0.5);
			double rayangley = camera->getAOF()*(x / (double)camera->getWidth() - 0.5);

			//calculate ray direction from angles
			Vector3 direction = Vector3(tan(rayanglex), tan(rayangley), 1);
			Ray ray = Ray(camera->getPosition(), direction);

			//start raytracer and get color
			RayTracer rt = RayTracer(ray);
			rt.startRay();
			Color color = rt.getColor();

			//set pixel color
			bitmap->set_pixel(x, y, color.getR(), color.getG(), color.getB());
		}
	}
}
