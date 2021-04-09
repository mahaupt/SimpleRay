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
#include <string>
#include <thread>
#include <vector>

#include "GameObject.h"
#include "RayTracer.h"
#include "bitmap_image.hpp"

class FrameBuffer;

class Camera : public GameObject {
 private:
  unsigned int width, height;
  double aof;

 public:
  Camera(Vector3 _position, int _width, int _height, double _aof);
  ~Camera();

  void renderToImage(std::string file);
  void renderToFB(FrameBuffer* framebuffer);
  static void renderThreadImage(Camera* camera, bitmap_image* bitmap,
                                unsigned int tid, unsigned int threadNumber);
  static void renderThreadFB(Camera* camera, FrameBuffer* bitmap,
                             unsigned int tid, unsigned int threadNumber);

  unsigned int getWidth() const { return width; }
  unsigned int getHeight() const { return height; }
  double getAOF() const { return aof; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////

class FrameBuffer {
  struct FB {
    unsigned char r, g, b;
  };

 private:
  FB* frameBuffer;
  unsigned int width, height;

 public:
  FrameBuffer(unsigned int _width, unsigned int _height);
  ~FrameBuffer();

  void* getData() { return frameBuffer; }
  unsigned int getWidth() { return width; }
  unsigned int getHeight() { return height; }
  void set_pixel(unsigned int x, unsigned int y, unsigned char r,
                 unsigned char g, unsigned char b);
};
