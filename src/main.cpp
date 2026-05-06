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
#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>
#include <future>

#include "Scene.h"

namespace {
constexpr int kWindowWidth = 1024;
constexpr int kWindowHeight = 768;
} // namespace

int initGL();
GLFWwindow *window;

int main() {
    // init opengl
    initGL();

    int framebufferWidth = 0;
    int framebufferHeight = 0;
    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);

    // create scene
    Scene myscene;
    myscene.createSphere(1, Vector3(0, 0, 0));
    myscene.createSphere(0.5, Vector3(0, -2, 0));
    myscene.createSphere(0.5, Vector3(0, 2, 0));
    myscene.createSphere(0.5, Vector3(2, 0, 0));
    myscene.createSphere(0.5, Vector3(-2, 0, 0));
    Cube &cube = myscene.createCube(1.5, Vector3(2.5, 0.5, 3));
    const double quarterTurn = std::acos(-1.0) / 4.0;
    cube.setRotation(
        Quaternion::fromAxisAngle(Vector3(0, 1, 0), quarterTurn) *
        Quaternion::fromAxisAngle(Vector3(1, 0, 0), quarterTurn));
    myscene.createLightSource(
        new Pointlight(Color(255, 255, 255), Vector3(4, 2, -1), 2, 1));
    /*myscene.createLightSource(
        new Pointlight(Color(255, 255, 255), Vector3(4, -2, 1), 1, 1));*/
    myscene.createLightSource(
        new Pointlight(Color(255, 255, 255), Vector3(1, 5, 0), 1, 1));
    Camera &cam = myscene.createCamera(Vector3(0, 0, -10), framebufferWidth,
                                       framebufferHeight);

    // start rendering scene:
    FrameBuffer frameBuffer = FrameBuffer(framebufferWidth, framebufferHeight);

    int parallel_count = 10;
    std::vector<std::future<void>> futures;
    for (int i = 0; i < parallel_count; i++) {
        futures.push_back(std::async(std::launch::async, Camera::renderThreadFB, &cam, &frameBuffer, i, parallel_count));
    }

    do {
        glViewport(0, 0, framebufferWidth, framebufferHeight);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // clear background screen to black
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glWindowPos2i(0, 0);
        glDrawPixels(frameBuffer.getWidth(), frameBuffer.getHeight(), GL_RGB,
                     GL_UNSIGNED_BYTE, frameBuffer.getData());

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

    for (int i = 0; i < futures.size(); i++) {
        futures[i].wait();
    }

    return 0;
}

int initGL() {
    // Initialise GLFW

    if (!glfwInit())

    {
        std::cerr << "Failed to initialize GLFW\n";
        return 1;
    }
    window = glfwCreateWindow(kWindowWidth, kWindowHeight, "SimpleRay Output",
                              NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to open GLFW window. If you have an Intel GPU, they "
                     "are not 3.3 compatible.\n";
        glfwTerminate();
        return 2;
    }
    glfwMakeContextCurrent(window);
    glEnable(GL_DEPTH_TEST);

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    return 0;
}
