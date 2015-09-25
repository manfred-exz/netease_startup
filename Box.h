//
// Created by manfred on 15-9-23.
//

#ifndef MODERN_OPENGL_BOX_H
#define MODERN_OPENGL_BOX_H
#include <glm/glm.hpp>
#include "param.h"
#include "utils.h"

const double world_limit = 2000;

class Box {
public:
	Box(Pos3D _origin, double _length);

	void render();

	static const unsigned int NUM_VERTICES = 8;
	CanvasPos canvasBuf[NUM_VERTICES];
private:
	Pos3D origin;
	double length;

	Pos3D ppos[NUM_VERTICES];
	glm::vec4 vec4Buf[NUM_VERTICES];

	void drawBoxBorder() const;
};




#endif //MODERN_OPENGL_BOX_H
