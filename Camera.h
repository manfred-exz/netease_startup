//
// Created by manfred on 15-9-24.
//

#ifndef NETEASE_STARTUP_CAMERA_H
#define NETEASE_STARTUP_CAMERA_H

#include "utils.h"

class Camera {
public:
	Camera();

	Camera(const Pos3D& _eye, const Pos3D& _center,  const Pos3D& _up, const double& _aspect);

	static mat4 lookAt(const Pos3D &eye, const Pos3D &up);

	static mat4 perspective(double distance, double aspect, double near, double far);

	static mat4 tranform(double near, double far, double top, double bottom, double left, double right);

private:
	Pos3D eye, center, up;
	double aspect;

};

#endif //NETEASE_STARTUP_CAMERA_H
