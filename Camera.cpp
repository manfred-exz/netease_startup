//
// Created by manfred on 15-9-24.
//

#include "Camera.h"

mat4 Camera::lookAt(const Pos3D& eye, const Pos3D& up) {
	glm::vec3 u, v, w;
	w = glm::normalize(eye);
	u = glm::normalize(glm::cross(up, w));
	v = glm::cross(w, u);

	auto lookat_m = glm::mat4(u.x, u.y, u.z, -u.x * eye.x - u.y * eye.y - u.z * eye.z,
	                          v.x, v.y, v.z, -v.x * eye.x - v.y * eye.y - v.z * eye.z,
	                          w.x, w.y, w.z, -w.x * eye.x - w.y * eye.y - w.z * eye.z,
	                          0, 0, 0, 1);

	lookat_m = glm::transpose(lookat_m);

	// You will change this return call
	return lookat_m;
}

Camera::Camera(const Pos3D &_eye, const Pos3D &_up, const double &_aspect) {
	eye = _eye;
	up = _up;
	aspect = _aspect;
}

Camera::Camera() {
	eye = Pos3D(0, 0, 5);
	up = Pos3D(0, 1, 0);
	aspect = 1;
}

mat4 Camera::perspective(double distance, double aspect, double near, double far) {
	auto &d = distance, &n = near, &f = far;
	auto a = -(f + n) / (f - n);
	auto b = -(2 * f * n) / (f - n);
	glm::mat4 mat(d / aspect, 0, 0, 0,
	              0, d, 0, 0,
	              0, 0, a, b,
	              0, 0, -1, 0);

	return glm::transpose(mat);
}


mat4 Camera::tranform(double near, double far, double top, double bottom, double left, double right) {
	auto &n = near, &f = far, &t = top, &b = bottom, &l = left, &r = right;
	return glm::mat4(2 / r - l, 0, 0, -(r + l) / (r - l),
	                 0, 2 / (t - b), 0, -(t + b) / (t - b),
	                 0, 0, 2 / (f - n), -(f + n) / (f - n),
	                 0, 0, 0, 1);
}
