
#pragma once
#define _USE_MATH_DEFINES
#include <cmath>




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
#include <algorithm>


#include <iostream>

#include <random>

#include <vector>

//#include <math.h>




//----
#include "Types.h"
#include "Array2D.h"
#include "Scene.h"
#include "Tetrahedron.h"
#include "LightObject.h"
#include "Sphere.h"



//Camera includer camera plane and the pixels in the camera
class Camera
{
public:

	Camera();

	~Camera();


	void render();

	void switchEye();

	void createImage(const std::string filename);

	glm::vec3 getAlbedo(Ray* ray);

	//bool isItMirror(Ray* ray);



	glm::vec3 rayRecursion(Ray* ray, int depth);
	//glm::vec3 setColor(Ray* ray);
	void castRay(Ray* ray);
	double lightRayFactor(Ray* ray);

	//glm::vec3 inDirectLight(Ray* ray, int russian);


	Scene* theScene = new Scene();
	LightObject* lamp = new LightObject(glm::vec3(1.0,1.0,1.0));
	Tetrahedron* theTetra = new Tetrahedron();
	Sphere* theSphere = new Sphere(1.1, glm::vec3(5.5f, 2.0f, 3.9f), ColorDbl(0, 0, 1), "mirror");
	Sphere* theSphereMatte = new Sphere(0.8, glm::vec3(9.9f, -3.0f, 1.5f), ColorDbl(1, 1, 1),"lambertian");
	Sphere* theSphereMatteBlue = new Sphere(1.0, glm::vec3(10.0f, 3.0f, 0.0f), ColorDbl(0, 0, 1), "lambertian");


	//size of camera plane
	//used for 2d array
	const int HEIGHT = 800; //y
	const int WIDTH = 800; //x


	int lightIndex;
	//Camera 1 and 2

   //Define the pair who holds the x and y coordinates for the eyes
   // Vertex eye1, eye2;
	Vertex eye1 = Vertex(-2.0f, 0.0f, 0.0f, 1.0); //CAMERA 1
	Vertex eye2 = Vertex(-1.0f, 0.0f, 0.0f, 1.0); //CAMERA 2


	 //Which camera is looking
	bool eye1IsWatching;

	bool isInWorldCoordinates = false;

	//Create imagePlane

	Array2D* imagePlane = new Array2D(HEIGHT, WIDTH);

	std::vector<Pixel*>::iterator ptr;

	double shadowRay(Ray* ray);

	bool lightFound = true;

	const double PIXEL_SIZE = 0.0025;

private:



};