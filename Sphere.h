#pragma once

// File and console I/O for logging and error reporting
#include <iostream>


// Math header for trigonometric functions
#include <cmath>

// another thing instead of GLFW
#include <glm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x2.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <vector>

//----
#include "Triangle.h"
#include "Types.h"


class Sphere
{

public:


	std::string itsSphere = "";
	ColorDbl color;

	glm::vec3 albedo = glm::vec3(1.0f, 1.0f, 1.0f);
	float radius;
	glm::vec3 point;


	Sphere(float rad, glm::vec3 p, ColorDbl c, std::string type);

	~Sphere();

	void rayIntersection(Ray* ray);

private:
};

