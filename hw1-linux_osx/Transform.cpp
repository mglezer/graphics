// Transform.cpp: implementation of the Transform class.


#include "Transform.h"

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	// YOUR CODE FOR HW1 HERE
	// Convert degrees to radians
	float rads = degrees * pi / 180;
	float k_x = axis[0];
	float k_y = axis[1];
	float k_z = axis[2];
	mat3 K = mat3(0, k_z, -1 * k_y, -1*k_z, 0, k_x, k_y, -1 * k_x, 0);
	return mat3() + sin(rads) * K + (1 - cos(rads)) * K * K;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
	// For left, the axis of rotation is always defined by the x-z plane, like lines of latitude,
	// so the rotation up-vector k is a constant.
	eye = rotate(degrees, vec3(0, 1, 0)) * eye;
	up = rotate(degrees, vec3(0, 1, 0)) * up;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	// For up, the axis of rotation is always relative to the current camera position, like lines of longitude,
	// so the rotation up-vector k is variable and always normal to the eye and current up vector.
	vec3 w = glm::normalize(eye); // assume center is 0,0,0
	vec3 u = glm::normalize(glm::cross(eye, up));
	eye = rotate(degrees, u) * eye;
	up = rotate(degrees, u) * up;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
	// YOUR CODE FOR HW1 HERE
	vec3 a = eye; // assume center is 0, 0, 0
	vec3 b = up;
	vec3 w = glm::normalize(a);
	vec3 u = glm::normalize(glm::cross(b, w));
	vec3 v = glm::cross(w, u);
	return mat4(u[0], v[0], w[0], 0, u[1], v[1], w[1], 0, u[2], v[2], w[2], 0, -1.0f * glm::dot(u, eye), -1.0f * glm::dot(v, eye), -1.0f * glm::dot(w, eye), 1);
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
