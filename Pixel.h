//
// Created by manfred on 15-9-22.
//

#ifndef MODERN_OPENGL_PIXEL_H
#define MODERN_OPENGL_PIXEL_H

#include <GL/gl.h>

class Pixel {
public:
	GLfloat r, g, b;

	Pixel(){}
	Pixel(const GLfloat& _red, const GLfloat& _green, const GLfloat& _blue):
			r(_red), g(_green), b(_blue){}
};


#endif //MODERN_OPENGL_PIXEL_H
