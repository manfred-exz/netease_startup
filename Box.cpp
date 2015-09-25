//
// Created by manfred on 15-9-23.
//
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Box.h"
#include "Canvas.h"
#include "Camera.h"
#include "Transform.h"

Box::Box(Pos3D _origin, double _length) {
	origin = _origin;
	length = _length/2;

//	std::vector<double> _vec;
//	_vec.push_back(_origin.x);
//	_vec.push_back(_origin.y);
//	_vec.push_back(_origin.z);
//
//	std::sort(_vec.begin(), _vec.end(), std::less<double>());
//
//	auto min_value = _vec[0];
//	auto max_value = _vec[2];
//
//	if (min_value < - world_limit || max_value + _length > world_limit) {
//		std::cerr << "Your object exceeds the world limit." << std::endl;
//	}

	if (_length >= world_limit) {
		std::cerr << "Your object exceeds the world limit." << std::endl;
	}

	/* set all 8 vertices of the cube box */
	ppos[0] = Pos3D(origin.x - length, origin.y - length, origin.z - length);
	ppos[1] = Pos3D(origin.x - length, origin.y + length, origin.z - length);
	ppos[2] = Pos3D(origin.x - length, origin.y + length, origin.z + length);
	ppos[3] = Pos3D(origin.x - length, origin.y - length, origin.z + length);

	ppos[4] = Pos3D(origin.x + length, origin.y - length, origin.z - length);
	ppos[5] = Pos3D(origin.x + length, origin.y + length, origin.z - length);
	ppos[6] = Pos3D(origin.x + length, origin.y + length, origin.z + length);
	ppos[7] = Pos3D(origin.x + length, origin.y - length, origin.z + length);
}

void Box::renderFold() {
	auto & eye = camera->eye;
	auto & up = camera->up;

	/* change to homogeneous coordinates */
	for (int i = 0; i < 8; ++i) {
		vec4Buf[i] = glm::vec4(ppos[i], 1);
	}

	/* rotate */
	auto rotate_m = Transform::rotate(-1, up);
	eye = rotate_m * eye;
	up = rotate_m * up;

	/* apply lookAt matrix */
	mat4 lookAt_m = Camera::lookAt(eye, up);

	/* apply perspective matrix */
	mat4 perspective_m = Camera::perspective(500, 1, 600, 1000);

	mat4 fold_m = perspective_m * lookAt_m;

	for (int i = 0; i < 8; ++i) {
		vec4Buf[i] = fold_m * vec4Buf[i];
	}

	/* scale everything in the 3D(float)-space down to 2D(int) space. */
	double factorX = 1 / world_limit * window_width;
	double factorY = 1 / world_limit * window_height;
	for (int i = 0; i < 8; ++i) {
		canvasBuf[i] = CanvasPos(vec4Buf[i].x / vec4Buf[i].w * factorX + window_width / 2,
		                         vec4Buf[i].y / vec4Buf[i].w * factorY + window_height / 2);
	}


	drawBoxBorder();
}

void Box::render() {
	auto & eye = camera->eye;
	auto & up = camera->up;

	/* change to homogeneous coordinates */
	for (int i = 0; i < 8; ++i) {
		vec4Buf[i] = glm::vec4(ppos[i], 1);
	}

	/* rotate */
	auto rotate_m = Transform::rotate(-1, up);
	eye = rotate_m * eye;
	up = rotate_m * up;

	/* apply lookAt matrix */
	/* verified */
//	std::cout << "look at" << std::endl;
	mat4 lookAt_m = Camera::lookAt(eye, up);
	for (int i = 0; i < 8; ++i) {
//		std::cout << "ppos[" << i << "] changed from (" << ppos[i].x << ", " << ppos[i].y << ", " << ppos[i].z << ") ";
		vec4Buf[i] = lookAt_m * vec4Buf[i];
//		std::cout << "to (" << vec4Buf[i].x << ", " << vec4Buf[i].y << ", " << vec4Buf[i].z << ", " << vec4Buf[i].w <<
//		") " << std::endl;
	}
//	std::cout << "[end]look at" << std::endl;


	/* apply perspective matrix */
	mat4 perspective_m = Camera::perspective(500, 1, 600, 1000);
//	std::cout << "the perspective matrix is ";
	const float *pSource = (const float *) glm::value_ptr(perspective_m);
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
//			std::cout << pSource[i * 4 + j] << ", ";
		}
//		std::cout << std::endl;
	}

	for (int i = 0; i < 8; ++i) {
		vec4Buf[i] = perspective_m * vec4Buf[i];
//		std::cout << "to (" << vec4Buf[i].x << ", " << vec4Buf[i].y << ", " << vec4Buf[i].z << ", " << vec4Buf[i].w <<
//		") " << std::endl;
	}

//	std::cout.flush();


	/* scale everything in the 3D(float)-space down to 2D(int) space. */
	double factorX = 1 / world_limit * window_width;
	double factorY = 1 / world_limit * window_height;
	for (int i = 0; i < 8; ++i) {
		canvasBuf[i] = CanvasPos(vec4Buf[i].x / vec4Buf[i].w * factorX + window_width / 2,
		                         vec4Buf[i].y / vec4Buf[i].w * factorY + window_height / 2);
	}

//	std::cout << "vertices position on screen." << std::endl;
	for (int i = 0; i < 8; ++i) {
//		std::cout << "to: (" << canvasBuf[i].x << ", " << canvasBuf[i].y << ") " << std::endl;
	}

	drawBoxBorder();
}

void Box::drawBoxBorder() const {/* draw the lines in the box */
	for (int i = 0; i < 4; ++i) {
		canvas->drawLine(canvasBuf[i], canvasBuf[(i + 1) % 4]);
	}

	for (int i = 0; i < 4; ++i) {
		canvas->drawLine(canvasBuf[i + 4], canvasBuf[(i + 1) % 4 + 4]);
	}

	for (int i = 0; i < 4; ++i) {
		canvas->drawLine(canvasBuf[i], canvasBuf[(i + 4) % 8]);
	}
}
