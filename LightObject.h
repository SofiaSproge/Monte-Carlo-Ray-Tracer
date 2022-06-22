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

//----
#include "Triangle.h"
#include "Types.h"


class LightObject
{
public:
	LightObject(glm::vec3 lightColorIn);

	~LightObject();

	std::string itsLamp = "light";
	glm::vec3 albedo = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	float lightIntesity = 100.0;

	void rayIntersection(Ray* ray);

	// vector storing all triangles that build upp the scene
	std::vector<Triangle*> lightVec;

	std::vector<Triangle*>::iterator lightP;

private:
	// All vertices for the scene/room
	Vertex v1, v2, v3, v4;

};

