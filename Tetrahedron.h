#pragma once


// File and console I/O for logging and error reporting
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

//----
#include "Triangle.h"
#include "Types.h"


class Tetrahedron
{
public:

	std::string itsTetra = "lambertian";

	std::vector<Triangle*> tetra;
	std::vector<Triangle*>::iterator tetraP;

	glm::vec3 albedo = glm::vec3(0.9f, 0.9f, 0.9f);


	Tetrahedron();

	~Tetrahedron();

	void rayIntersection(Ray* ray);

private:

	//Tetrahederon 1
	Vertex vtop, vfront, vbottom1, vbottom2;

	//Tetrahederon 2
	Vertex vtop_2, vfront_2, vbottom1_2, vbottom2_2;


};

