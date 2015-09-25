//
// Created by manfred on 15-9-23.
//

#ifndef MODERN_OPENGL_TRANSFORM_H
#define MODERN_OPENGL_TRANSFORM_H


#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// glm provides vector, matrix classes like glsl
// Typedefs to make code more readable

typedef glm::mat3 mat3 ;
typedef glm::mat4 mat4 ;
typedef glm::vec3 vec3 ;
typedef glm::vec4 vec4 ;
const float pi = 3.14159265f; // For portability across platforms


class Transform
{
public:
	Transform() { }

	virtual ~Transform() { }

	static void left(float degrees, vec3& eye, vec3& up);
	static void up(float degrees, vec3& eye, vec3& up);
	static mat4 lookAt(vec3 eye, vec3 up);
	static mat3 rotate(const float degrees, const vec3& axis) ;
};



#endif //MODERN_OPENGL_TRANSFORM_H
