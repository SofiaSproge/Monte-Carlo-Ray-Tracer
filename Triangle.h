#pragma once
#include <iostream>
// Math header for trigonometric functions
#include <cmath>

// GLM
#include <glm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x2.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <vector>


#include "Types.h"

class Triangle
{

public:

	Triangle(Vertex vertex0, Vertex vertex1, Vertex vertex2, ColorDbl colorIn, Direction direc, std::string stringIn);

	~Triangle();


	Vertex v0, v1, v2; // vertex for the triangle
	glm::vec3 e1, e2; // vectors to use when calc normal
	Direction normal;
	ColorDbl color; 
	std::string type = "";

	//Function that checks if you have an intersection point with a triangle when you shoot a ray
	//Set INF (infinity) to 9999999999, make the ray as long as possible to give it a change to intersect
	//sPos is the starting position, direction is a normal 
	bool intersection(glm::vec3 sPos, Direction direction, float& t);


};

