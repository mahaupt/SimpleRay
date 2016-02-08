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

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "OpenGL32.lib")
#include <gl/glfw3.h>
#include <iostream>

#include "Scene.h"


int initGL();
GLFWwindow* window;



int main() {
	//init opengl
	initGL();

	//create scene
	Scene myscene;
	myscene.createSphere(1, Vector3(0, 0, 0));
	myscene.createSphere(0.5, Vector3(0, -2, 0));
	myscene.createSphere(0.5, Vector3(0, 2, 0));
	myscene.createSphere(0.5, Vector3(2, 0, 0));
	myscene.createSphere(0.5, Vector3(-2, 0, 0));
	Camera & cam = myscene.createCamera(Vector3(0, 0, -5));

	//start rendering scene:
	//cam.renderToImage("image.bmp");
	FrameBuffer frameBuffer = FrameBuffer(1024, 768);
	//cam.renderToFB(&frameBuffer);

	std::thread t1 = std::thread(Camera::renderThreadFB, &cam, &frameBuffer, 0, 1);
	//std::thread t2 = std::thread(Camera::renderThreadFB, &cam, &frameBuffer, 1, 2);

	do {
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //clear background screen to black
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawPixels(frameBuffer.getWidth(), frameBuffer.getHeight(), GL_RGB, GL_UNSIGNED_BYTE, frameBuffer.getData());


		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	t1.join();
	//t2.join();

	return 0;
}



int initGL() {
	// Initialise GLFW

	if (!glfwInit())

	{
		std::cerr << "Failed to initialize GLFW\n";
		return 1;
	}
	glEnable(GL_DEPTH_TEST);

	window = glfwCreateWindow(1024, 768, "SimpleRay Output", NULL, NULL);
	if (window == NULL) {
		std::cerr << "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n";
		glfwTerminate();
		return 2;
	}
	glfwMakeContextCurrent(window);
	
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	return 0;
}