//
// Created by manfred on 15-9-23.
//

#include "Transform.h"

mat4 Transform::lookAt(vec3 eye, vec3 up) {
	glm::vec3 u, v, w;
	w = glm::normalize(eye);
	u = glm::normalize(glm::cross(up, w));
	v = glm::cross(w, u);


	auto lookat_m = glm::mat4(u.x, u.y, u.z, -u.x * eye.x - u.y * eye.y - u.z * eye.z,
	                          v.x, v.y, v.z, -v.x * eye.x - v.y * eye.y - v.z * eye.z,
	                          w.x, w.y, w.z, -w.x * eye.x - w.y * eye.y - w.z * eye.z,
	                          0, 0, 0, 1);

	lookat_m = glm::transpose(lookat_m);

	return lookat_m;
}

float toRadians(const float degrees) {
	return pi * degrees / 180;
}

mat3 Transform::rotate(const float degrees, const vec3 &axis) {
	auto x = axis.x, y = axis.y, z = axis.z;
	auto radians = toRadians(degrees);

	auto rotate_m = (float)cos(radians) * mat3(1, 0, 0, 0, 1, 0, 0, 0, 1) +
			(float)(1 - cos(radians)) * mat3(x * x, x * y, x * z, x * y, y * y, y * z, x * z, y * z, z * z) +
			(float)sin(radians) * mat3(0, z, -y, -z, 0, x, y, -x, 0);

	return rotate_m;
}

//void Transform::left(float degrees, vec3 &eye, vec3 &up) {
//	auto rotate_axis = up;
//	auto rotate_m = rotate(-degrees, rotate_axis);
//
//	eye = rotate_m * eye;
//	up = rotate_m * up;
//}
//
//void Transform::up(float degrees, vec3 &eye, vec3 &up) {
//	auto rotate_axis = glm::cross(glm::normalize(eye), up);
//	auto rotate_m = rotate(-degrees, rotate_axis);
//
//	eye = rotate_m * eye;
//	up = rotate_m * up;
//}
