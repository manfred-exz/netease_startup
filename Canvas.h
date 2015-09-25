//
// Created by manfred on 15-9-22.
//

#ifndef MODERN_OPENGL_CANVAS_H
#define MODERN_OPENGL_CANVAS_H
#include <vector>
#include "param.h"
#include "utils.h"

typedef Pixel CanvasColor;

class Canvas {
public:
	Canvas(int width = 800, int height = 800);

	void clear(GLfloat red = 0, GLfloat green = 0, GLfloat blue = 0);

	void update();

	void drawLine(const CanvasPos& startPos, const CanvasPos& endPos);

	inline void setPoint(const CanvasPos& pos, const GLfloat& r, const GLfloat& g, const GLfloat& b){
		pixel(pos.x, pos.y) = Pixel(r, g, b);
	}

	inline void setPoint(const int x, const int y, const GLfloat& r, const GLfloat& g, const GLfloat& b){
		pixel(x, y) = Pixel(r, g, b);
	}

	inline void setPoint(const int& x, const int& y, const CanvasColor& color){
		pixel(x, y) = color;
	}

	inline Pixel& pixel(const int & x, const int & y){
		return m_pixels[y*window_width + x];
	}

private:
	Pixel* m_pixels;
	int m_width, m_height;

public:
	void setBrushColor(const CanvasColor &brushColor) {
		Canvas::brushColor = brushColor;
	}

private:
/* paint tool state */
	CanvasColor brushColor;


};


#endif //MODERN_OPENGL_CANVAS_H
