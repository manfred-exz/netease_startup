//
// Created by manfred on 15-9-22.
//
#include <cmath>
#include <glm/glm.hpp>
#include "utils.h"
#include "Canvas.h"
#include "Box.h"

unsigned int window_width = 800, window_height = 800;
const int window_size = window_width * window_height;

Canvas::Canvas(int width, int height) {
	m_width = width;
	m_height = height;
	// pre-allocate memory for all the pixels on the canvas.
	GLfloat *_floats = new GLfloat[window_size * 3];
	m_pixels = (Pixel *) _floats;
	clear();
}

void Canvas::clear(GLfloat r, GLfloat g, GLfloat b) {
	for(int i = 0; i < m_height; i++)
		for(int j = 0; j < m_width; j++){
			auto & _pixel = m_pixels[i*m_height + j];
			_pixel.r = r;
			_pixel.g = g;
			_pixel.b = b;
		}
}

void Canvas::update() {
	glRasterPos2d(-1, -1);
	setBrushColor(CanvasColor(1, 1, 1));

	/* TEST */
	/* draw a line in 2D space. */

//	drawLine(CanvasPos(0, 0), CanvasPos(0, 400));
//	drawLine(CanvasPos(0, 400), CanvasPos(400, 400));
//	drawLine(CanvasPos(400, 0), CanvasPos(400, 400));
//	drawLine(CanvasPos(400, 0), CanvasPos(0, 0));


	box->render();

	glDrawPixels(window_width, window_height, GL_RGB, GL_FLOAT, m_pixels);
}


/* modified Bresenham's line algorithm
 * wiki: https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
 * todo: should sort start, end pos in x-value order first. and out-of-screen pixels should be drawn */

void Canvas::drawLine(const CanvasPos &startPos, const CanvasPos &endPos) {
	// convert to integer position to raster
//	auto startPos = Pos2D(a);
//	auto endPos = Pos2D(b);

	auto deltaX = endPos.x - startPos.x;
	auto deltaY = endPos.y - startPos.y;


	int signSlope = deltaY/(double)deltaX >= 0 ? 1 : -1;
	int signX = deltaX >= 0 ? 1 : -1;
	int signY = deltaY >= 0 ? 1 : -1;

	if(deltaX == 0){
		for (int yPos = startPos.y; yPos != endPos.y; yPos += signY) {
			setPoint(startPos.x, yPos, brushColor);
		}
		return;
	}

	double err = 0;

	double deltaErr = fabs(deltaY/(double)deltaX);

	for(int xPos = startPos.x, yPos = startPos.y;
	    xPos != endPos.x; xPos += signX)
	{
		/* draw the pixel. */
		setPoint(xPos, yPos, brushColor);

		/* accumulate err for every pixel drawn. */
		err += deltaErr;
		while(err >= 0.5){
			setPoint(xPos, yPos, brushColor);
			yPos += signSlope * signX;
			err -= 1;
		}
	}
}
