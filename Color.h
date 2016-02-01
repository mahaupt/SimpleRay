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
class Color
{
private:
	unsigned char r, g, b;
public:
	Color();
	Color(unsigned char _r, unsigned char _g, unsigned char _b);
	~Color();

	//getters and setters
	unsigned char getR() { return r; }
	unsigned char getG() { return g; }
	unsigned char getB() { return b; }
	void setR(unsigned char _r) { r = _r; }
	void setG(unsigned char _g) { g = _g; }
	void setB(unsigned char _b) { b = _b; }
};

