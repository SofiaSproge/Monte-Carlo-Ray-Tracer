
#include "Scene.h"



Scene::Scene() {

	v1 = Vertex(0.0f, 6.0f, -5.0f, 1.0);
	v2 = Vertex(-3.0f, 0.0f, -5.0f, 1.0);
	v3 = Vertex(5.0f, 0.0f, -5.0f, 1.0);
	v4 = Vertex(10.0f, 6.0f, -5.0f, 1.0);
	v5 = Vertex(13.0f, 0.0f, -5.0f, 1.0);
	v6 = Vertex(10.0f, -6.0f, -5.0f, 1.0);
	v7 = Vertex(0.0f, -6.0f, -5.0f, 1.0);
	v8 = Vertex(-3.0f, 0.0f, 5.0f, 1.0);
	v9 = Vertex(0.0f, 6.0f, 5.0f, 1.0);
	v10 = Vertex(10.0f, 6.0f, 5.0f, 1.0);
	v11 = Vertex(5.0f, 0.0f, 5.0f, 1.0);
	v12 = Vertex(13.0f, 0.0f, 5.0f, 1.0);
	v13 = Vertex(10.0f, -6.0f, 5.0f, 1.0);
	v14 = Vertex(0.0f, -6.0f, 5.0f, 1.0);


	//extra triangle
	/*Vertex v1a(8.0f, 3.0f, 3.0f, 1.0);
	Vertex v2a(8.0f, -3.0f, 3.0f, 1.0);
	Vertex v3a(8.0f, 0.0f, -3.0f, 1.0);

	sceneRoom.push_back(new Triangle(v1a, v3a, v2a, glm::vec3(0.88f, 0.607f, 0.607f),Direction(), itsScene)); //fake triangle

	*/


	// FLOOR WHITE
	sceneRoom.push_back(new Triangle(v1, v2, v3, glm::vec3(1.0f, 1.0f, 1.0f), Direction(), itsScene)); //T1
	sceneRoom.push_back(new Triangle(v1, v3, v4, glm::vec3(1.0f, 1.0f, 1.0f), Direction(), itsScene)); //T2
	sceneRoom.push_back(new Triangle(v4, v3, v5, glm::vec3(1.0f, 1.0f, 1.0f), Direction(), itsScene)); //T3
	sceneRoom.push_back(new Triangle(v3, v6, v5, glm::vec3(1.0f, 1.0f, 1.0f), Direction(), itsScene)); //T4
	sceneRoom.push_back(new Triangle(v3, v7, v6, glm::vec3(1.0f, 1.0f, 1.0f), Direction(), itsScene)); //T5
	sceneRoom.push_back(new Triangle(v3, v2, v7, glm::vec3(1.0f, 1.0f, 1.0f), Direction(), itsScene)); //T6


	//ROOF WHITE
	sceneRoom.push_back(new Triangle(v8, v9, v11, glm::vec3(1.0f, 1.0f, 1.0f), Direction(), itsScene)); //T1
	sceneRoom.push_back(new Triangle(v9, v10, v11, glm::vec3(1.0f, 1.0f, 1.0f), Direction(), itsScene)); //T2
	sceneRoom.push_back(new Triangle(v11, v10, v12, glm::vec3(1.0f, 1.0f, 1.0f), Direction(), itsScene)); //T3
	sceneRoom.push_back(new Triangle(v11, v12, v13, glm::vec3(1.0f, 1.0f, 1.0f), Direction(), itsScene)); //T4
	sceneRoom.push_back(new Triangle(v14, v11, v13, glm::vec3(1.0f, 1.0f, 1.0f), Direction(), itsScene)); //T5
	sceneRoom.push_back(new Triangle(v11, v14, v8, glm::vec3(1.0f, 1.0f, 1.0f), Direction(), itsScene)); //T6

	/*WALLS CLOSEST TO US*/
	// Wall 1 LIGHT BLUE 8DA1C8
	sceneRoom.push_back(new Triangle(v8, v14, v2, glm::vec3(0.0f, 1.0f, 0.0f), Direction(), itsScene)); //T1
	// Wall 2
	sceneRoom.push_back(new Triangle(v14, v7, v2, glm::vec3(0.0f, 1.0f, 0.0f), Direction(), itsScene)); //T2
	// Wall 3 MINT GREEN C5ECD8
	sceneRoom.push_back(new Triangle(v14, v6, v7, glm::vec3(0.0f, 1.0f, 0.0f), Direction(), itsScene)); //T3
	// Wall 4
	sceneRoom.push_back(new Triangle(v14, v13, v6, glm::vec3(0.0f, 1.0f, 0.0f), Direction(), itsScene)); //T4
	// Wall 5 LIGHT PEACH E1B79B THIIIIS
	sceneRoom.push_back(new Triangle(v13, v12, v6, glm::vec3(1.0f, 1.0f, 1.0f), Direction(), itsScene)); //T5
	// Wall 6
	sceneRoom.push_back(new Triangle(v6, v12, v5, glm::vec3(1.0f, 1.0f, 1.0f), Direction(), itsScene)); //T6

	/*WALLS MOST FAR FROM TO US*/
	// Wall 1 PINK E19BDF
	sceneRoom.push_back(new Triangle(v8, v2, v9, glm::vec3(0.5f, 0.5f, 1.0f), Direction(), itsScene)); //T1
	// Wall 2
	sceneRoom.push_back(new Triangle(v2, v1, v9, glm::vec3(0.5f, 0.5f, 1.0f), Direction(), itsScene)); //T2
	// Wall 3 WARM PINK E19B9B
	sceneRoom.push_back(new Triangle(v9, v1, v4, glm::vec3(0.5f, 0.5f, 1.0f), Direction(), itsScene)); //T3
	// Wall 4
	sceneRoom.push_back(new Triangle(v9, v4, v10, glm::vec3(0.5f, 0.5f, 1.0f), Direction(), itsScene)); //T4
	// Wall 5 DARKER MINT GREEN 9BE19B
	sceneRoom.push_back(new Triangle(v10, v4, v12, glm::vec3(1.0f, 1.0f, 1.0f), Direction(), itsScene)); //T5
	// Wall 6
	sceneRoom.push_back(new Triangle(v4, v5, v12, glm::vec3(1.0f, 1.0f, 1.0f), Direction(), itsScene)); //T6

};

Scene::~Scene() {

	for (pointer = sceneRoom.begin(); pointer != sceneRoom.end(); ++pointer) {
		delete (*pointer);
	}
	sceneRoom.clear();
}






// Delete !! in https: before paste into web
// https:!!//www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays
void Scene::rayIntersection(Ray* ray) {

	std::vector<Triangle*>::iterator pointer2;

	//std::cout << "Inside RayIntersection in Scene.cpp" << std::endl;
	float rayLength = INFINITY;

	glm::vec3 intersectedP;

	//Triangle intersection wants startpos direction and t
	//We need a for loop to go through the vector sceneRoom


	for (pointer2 = sceneRoom.begin(); pointer2 != sceneRoom.end(); pointer2++) {


		float t = INFINITY;

		if ((*pointer2)->intersection(ray->start.position, ray->direction, t) && (t < rayLength))
		{

			rayLength = t; // used as reference, maybe change in intersection, declare it again
		//	std::cout << rayLength  << std::endl;

			ray->color = (*pointer2)->color; // giving the ray the color that the triangle has

			ray->end = Vertex(glm::vec3(ray->start.position + (ray->direction.vec * rayLength)));

			//save the legth of the ray from startpoint to hitpoint
			ray->triangleIntersectNormal = (*pointer2)->normal.vec;

			ray->tLength = rayLength;

			ray->objectType = (*pointer2)->type;

		}

	}


}


