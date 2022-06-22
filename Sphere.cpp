#include "Sphere.h"


Sphere::Sphere(float rad, glm::vec3 p, ColorDbl c, std::string type) : radius{ rad }, point{ p }, color{ c }, itsSphere{ type }{
	//std::cout << "Creating Sphere" << std::endl;
}

Sphere::~Sphere() {};

void Sphere::rayIntersection(Ray* ray) {

	float minDist = 1000;
	float discriminant;
	float d1, d2;

	//Vertex o = ray->start.; ray.pos
	//Direction l = ray.getDirection(); l är ray direc

	float a = 1; //Since the direction is normalized
	float b = 2.0f * glm::dot(ray->direction.vec, (ray->start.position - point));
	float c = glm::dot((ray->start.position - point), (ray->start.position - point)) - pow(radius, 2);

	discriminant = b * b - 4.0f * a * c;
	glm::vec3 tempIntersection;

	// No solutions
	if (discriminant < 0) {
		return;
	}

	//One solution
	else if (discriminant < DBL_EPSILON) {
		d1 = -(b / 2.0f);
		tempIntersection = ray->start.position + d1 * ray->direction.vec;
	}
	//Two solutions
	else {
		d1 = -(b / 2.0f) + sqrt(pow((b / 2.0f), 2) - a * c);
		d2 = -(b / 2.0f) - sqrt(pow((b / 2.0f), 2) - a * c);

		if (d2 > 0.0f) {
			tempIntersection = ray->start.position + d2 * ray->direction.vec;
		}
		else if (d1 > 0.0f) {
			tempIntersection = ray->start.position + d1 * ray->direction.vec;
		}
		else return;
	}

	if (glm::length(tempIntersection - ray->start.position) < minDist) {
		minDist = glm::length(tempIntersection - ray->start.position);
		Direction normal = glm::normalize(tempIntersection - point);
		ray->triangleIntersectNormal = normal.vec;
		ray->color = color;
		ray->end.position = tempIntersection + normal.vec * 0.001f;
		ray->objectType = itsSphere;
		ray->tLength = abs(glm::length(ray->start.position - ray->end.position));
	}


}

