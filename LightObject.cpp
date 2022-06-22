#pragma once
#include "LightObject.h"

LightObject::LightObject(glm::vec3 lightColorIn) :lightColor{lightColorIn} {

	v1 = Vertex(7.0f, 1.5f, -4.999f, 1.0);
	v2 = Vertex(10.0f, 1.5f, -4.999f, 1.0);
	v3 = Vertex(10.0f, -1.5f, -4.999f, 1.0);
	v4 = Vertex(7.0f, -1.5f, -4.999f, 1.0);

	lightVec.push_back(new Triangle(v1, v2, v3, lightColorIn, Direction(), itsLamp)); //w1
	lightVec.push_back(new Triangle(v1, v3, v4, lightColorIn, Direction(), itsLamp)); //w1

}

LightObject::~LightObject() {

	for (lightP = lightVec.begin(); lightP != lightVec.end(); ++lightP) {
		delete (*lightP);
	}
	lightVec.clear();

}


void LightObject::rayIntersection(Ray* ray) {

	std::vector<Triangle*>::iterator lightP2;

	//std::cout << "Inside RayIntersection in Tetrahederon.h" << std::endl;
	float rayLength = INFINITY;

	glm::vec3 intersectedP;

	//Triangle intersection wants startpos direction and t
	//We need a for loop to go through the vector tetra

	for (lightP2 = lightVec.begin(); lightP2 != lightVec.end(); lightP2++) {



		float t = INFINITY;


		if ((*lightP2)->intersection(ray->start.position, ray->direction, t) && (t < rayLength))
		{

			//ska tillföra ljus till objektet

			rayLength = t; // used as reference, maybe change in intersection, declare it again

			ray->color = (*lightP2)->color; // giving the ray the color that the triangle has

			ray->end = Vertex(glm::vec3(ray->start.position + (ray->direction.vec * rayLength)));

			ray->triangleIntersectNormal = (*lightP2)->normal.vec;
			//save the legth of the ray from startpoint to hitpoint
			ray->tLength = rayLength;

			ray->objectType = (*lightP2)->type;

		}

	}


}

