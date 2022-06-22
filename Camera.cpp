#pragma once
#include "Camera.h"


std::default_random_engine generator;
std::uniform_real_distribution<float> distributionX(7.0f, 10.0f); //x axeln
std::uniform_real_distribution<float> distributionY(-1.5f, 1.5f); //y axeln
std::uniform_real_distribution<float> distributionRandomR1(0.0f, 1.0f); //used to generate random secondaryrays
//std::uniform_real_distribution<float> distributionRandomR2(0.0f, 1.0f);

Camera::Camera() {

	std::cout << "Instance of camera has been created => A instance of Scene, tetra, lamp and sphere is created " << std::endl;

	switchEye();
	std::cout << "Creating Camera: Image Plane and two eyes" << std::endl;

	Camera::render();
	std::cout << "Rendering step is finished" << std::endl;

	Camera::createImage("picture2.ppm");
}

Camera::~Camera() {};


//launches a ray through each pixel one at a time and sets the pixel value
// go thorugh height and width???
void Camera::render() {

	//Getting camera possition and will be used as starting points for our primary rays
	Vertex* eye;
	if (eye1IsWatching) {
		//eye = &eye1;
		eye = &eye1;
	}
	else {
		eye = &eye2;
	}

	std::cout << "Camera::Render, we set every color" << std::endl;


	for (int y = 0; y < WIDTH; y++) {
		for (int x = 0; x < HEIGHT; x++) {

			//Create a ray that has start point from  eye 1 or eye2 that has a direction that goes through the 
			//center of currentPixel and contues in the same direction out into the scene.
			//call rayInterection to recieve triangle or get color and enpoint.


			//creating primary Rays

			//Get a pixel

			Pixel* currentPixel = imagePlane->get(x, y); // får postion, var denna punkt finns i container

			
			//Find the direction betwwen eye and our pixel center
			//end=start + direction*t => direction = end-start/t 
			glm::vec3 direc = glm::normalize((currentPixel->pixelCenter.position - eye->position));
			
			glm::vec3 resultColor = glm::vec3(0.0, 0.0, 0.0);
			int samples = 10;

			for (int i = 0; i < samples; i++) {
				//simple program for only one ray (will be modified later!!!!!!!)
				Ray* primaryRay = new Ray(eye->position, Direction(direc));

				castRay(primaryRay);

				resultColor += rayRecursion(primaryRay, 0);
				delete primaryRay;
			}

			resultColor /= (float)samples;

			currentPixel->colorP = ColorDbl(resultColor);

			if (x % 100 == 0 || y % 100 == 0) {
				std::cout << "rendered: (" << x << "," << y << ")" << std::endl;
			}
		

			
		}
	}

}


double Camera::lightRayFactor(Ray* ray) {
	//Im pretty sure the random coordinates is the middle of the lamp but this is bad programming practice
	glm::vec3 lightRayDirection = glm::normalize(glm::vec3(8.5, 0, -4.999f) - ray->end.position);

	double factor = (std::max(0.0f, (glm::dot(ray->triangleIntersectNormal, (lightRayDirection)))));

	return factor;
	
}



//cast rays to intersect with one object in the scene
void Camera::castRay(Ray* ray) {
	//NOOOOTTIIISEE  Denna kommer skriva över rayen du skickar in !! 
	theScene->rayIntersection(ray);

	lamp->rayIntersection(ray);

	theTetra->rayIntersection(ray);

	theSphere->rayIntersection(ray);

	theSphereMatte->rayIntersection(ray);

	theSphereMatteBlue->rayIntersection(ray);

}

glm::vec3 Camera::rayRecursion(Ray* ray, int depth) {
	
	if (depth > 2)
	{
		return glm::vec3(0.0,0.0,0.0);
	}

	//Check the surface and decide if reflected or executed. Mirror will reflect and lambertian will return the color value
	if (ray->objectType == "lambertian") {
		//an lambertian object

		//compute direct light
		glm::vec3 directLight = glm::vec3(0.0, 0.0, 0.0);

		double shadow = shadowRay(ray);

		if (shadow != 0.0) {

			//The falloff when a object is further from the light source
			double lightFactor = lightRayFactor(ray);

			//directLight = visible * lamp->lightColor * ray->color * lengthFactor
			//directLight = directLight * glm::vec3(lengthFactor, lengthFactor, lengthFactor);

			directLight.r = shadow * lightFactor * lamp->lightColor.r * ray->color.red;
			directLight.g = shadow * lightFactor * lamp->lightColor.g * ray->color.green;
			directLight.b = shadow * lightFactor * lamp->lightColor.b * ray->color.blue;

		}



		//create the coordinate system
		Direction N, Nt, Nb;

		N = ray->triangleIntersectNormal;
		//Nt, Nb;

		if (std::fabs(N.vec.x) > std::fabs(N.vec.y)) {
			float temp = (float)sqrtf(N.vec.x * N.vec.x + N.vec.z * N.vec.z);
			Nt = Direction(N.vec.z / temp, 0.0f, -N.vec.x / temp);
		}
		else {
			float temp = (float)sqrtf(N.vec.y * N.vec.y + N.vec.z * N.vec.z);
			Nt = Direction(0.0f, -N.vec.z / temp, N.vec.y / temp);
		}
		Nb = glm::cross(N.vec, Nt.vec);


		//compute indirect light
		glm::vec3 indirectLight = glm::vec3(0.0, 0.0, 0.0);

		Ray* secondaryRay;

		int q = 2;

		for (int i = 0; i < q; i++) {

			float r1 = distributionRandomR1(generator);
			float r2 = distributionRandomR1(generator);

			//float pdf = 1 / (2 * M_PI);
			float sinTheta = sqrtf(1.0f - r1 * r1); //trigonometriska ettan , vinkel
			float pdf = M_PI;
			float phi = 2.0 * M_PI * r2;
			float x = sinTheta * cosf(phi);
			float z = sinTheta * sinf(phi);

			Direction sampleDirection = Direction(x, r1, z);

			Direction sampleDirectionWorld(
				sampleDirection.vec.x * Nb.vec.x + sampleDirection.vec.y * N.vec.x + sampleDirection.vec.z * Nt.vec.x,
				sampleDirection.vec.x * Nb.vec.y + sampleDirection.vec.y * N.vec.y + sampleDirection.vec.z * Nt.vec.y,
				sampleDirection.vec.x * Nb.vec.z + sampleDirection.vec.y * N.vec.z + sampleDirection.vec.z * Nt.vec.z
			);

			secondaryRay = new Ray(ray->end.position, glm::normalize(sampleDirectionWorld.vec));

			//intersect with the objects
			castRay(secondaryRay);

			indirectLight += (rayRecursion(secondaryRay, depth + 1) * glm::vec3(r1, r1, r1) / glm::vec3(pdf,pdf,pdf) );

			delete secondaryRay;
		}

		indirectLight = indirectLight/ glm::vec3((float)q, (float)q, (float)q);

	//	return (indirectLight + directLight) / glm::vec3(M_PI, M_PI, M_PI) * getAlbedo(ray);

		return ((indirectLight * glm::vec3(2.0, 2.0, 2.0)) + (directLight / glm::vec3(M_PI, M_PI, M_PI))) * getAlbedo(ray);
	}

	else if (ray->objectType == "mirror") {
		//This is a mirror object

		glm::vec3 direc2 = glm::normalize(ray->direction.vec - (glm::dot(ray->direction.vec, ray->triangleIntersectNormal) * 2 * ray->triangleIntersectNormal));

		Ray* secondaryRay = new Ray(ray->end.position, Direction(direc2));

		castRay(secondaryRay);

		return rayRecursion(secondaryRay, depth + 1);
	}
	else
	{
		//is a lamp  
		float lamp_r = ray->color.red;
		float lamp_g = ray->color.green;
		float lamp_b = ray->color.blue;

		glm::vec3 lampColor = glm::vec3(lamp_r,lamp_g,lamp_b);

		//return  (lampColor + rayRecursion(ray, depth + 1));
		//return (glm::vec3(0.0, 0.0, 0.0)) + rayRecursion(ray, depth + 1);

		
		return lampColor;
		//return setColor(ray);
	}

	

}




//used in rednering equation. if in shadow will return 1 we render the color
//0 returns black. we use it directly in the rendering eq
double Camera::shadowRay(Ray* ray) {

	//start with sending shadow ray

	int nbrOfShadowsTests = 2; // how many shadow rays do we send
	int nbrOfshadow = 0;
	int nbrOflight = 0;
	double res = 0;

	Vertex randomLightPos = Vertex(); // used to get a vertex point on lamp

	for (int i = 0; i < nbrOfShadowsTests; i++) {

		randomLightPos.position.x = distributionX(generator);
		randomLightPos.position.y = distributionY(generator);
		randomLightPos.position.z = -4.999f;


		//displace the origin of the ray to avoid shadow acne
		float shadowBias = 0.01;
		glm::vec3 newPos = ray->end.position + glm::vec3(ray->triangleIntersectNormal.x * shadowBias, ray->triangleIntersectNormal.y * shadowBias, ray->triangleIntersectNormal.z * shadowBias);


		//send shadowray
		glm::vec3 shadowDirec = glm::normalize((randomLightPos.position - newPos));



		Ray* sentShadowRay = new Ray(newPos, shadowDirec);

		//NOTE Dont intersect with the lamp!!
		theScene->rayIntersection(sentShadowRay); //Vad händer om vi intersectar tetrahedron först men sedan ett objekt närmare. Kan t potensiellt skrivas över (både bra och dåligt)

		theTetra->rayIntersection(sentShadowRay);

		theSphere->rayIntersection(sentShadowRay);

		theSphereMatte->rayIntersection(sentShadowRay);

		theSphereMatteBlue->rayIntersection(sentShadowRay);


		if ((sentShadowRay->tLength < INFINITY) && (glm::length(sentShadowRay->end.position - newPos) < glm::length(randomLightPos.position - newPos))) {
			//&& abs(glm::length(sentShadowRay->end.position - randomLightPos.position)) > 1.0f
			nbrOfshadow++;
		}
		else {

			nbrOflight++;
			res = res + 1;
		}

		ray->shadowRayLength = abs(glm::length(sentShadowRay->end.position - newPos));

		delete sentShadowRay;
	}


	return res / nbrOfShadowsTests;

	
}


void Camera::switchEye() {
	int option = -1;

	std::cout << "Enter 1 for eye1 and enter 2 for eye 2" << std::endl;
	std::cin >> option;
	switch (option) {
	case 1:
		std::cout << "You have chosen EYE1" << endl;
		eye1IsWatching = true;
		break;

	case 2:
		std::cout << "You have chosen EYE2" << endl;
		eye1IsWatching = false;
		break;

	default:
		std::cout << "No legitamate answer, We give you Eye1" << endl;
		eye1IsWatching = false;
		break;
	}
}

//prints the picture into a file on harddrive
void Camera::createImage(const std::string filename) {
	//remember that you might want to create a pretty dynamic range, you might want to cosider using max
	std::cout << "Camera::CreateImage : creates a file with image" << std::endl;
	FILE* myFile = fopen(filename.c_str(), "wb");

	(void)fprintf(myFile, "P3\n%d %d\n255\n", WIDTH, HEIGHT);



	//normalize
	//double theMax = getMax();
	float gamma = 1/ 2.0f;

	for (int y = 0; y < WIDTH; y++) {
		for (int x = 0; x < HEIGHT; x++) {
			const Pixel* currentPixel = imagePlane->get(x, y);
			//	std::cout << "Pixel color: " << currentPixel->colorP.red << " " << currentPixel->colorP.green << " " << currentPixel->colorP.blue << std::endl;
			/*(void)fprintf(myFile, "%d %d %d ",
				(int)(round(255 * (currentPixel->colorP.red) / ((theMax)))),
				(int)(round(255 * (currentPixel->colorP.green) / ((theMax)))),
				(int)(round(255 * (currentPixel->colorP.blue) / ((theMax)))));*/

			(void)fprintf(myFile, "%d %d %d ",
				(int)((glm::clamp((float)(glm::pow(currentPixel->colorP.red, gamma)), 0.0f, 1.0f) * 255)),
				(int)((glm::clamp((float)(glm::pow(currentPixel->colorP.green, gamma)), 0.0f, 1.0f) * 255)),
				(int)((glm::clamp((float)(glm::pow(currentPixel->colorP.blue, gamma)), 0.0f, 1.0f) * 255)));
		}

		//char(int(glm::clamp(glm::pow(irradiance_values[index][0], gamma), 0.0f, 1.0f) * 255));
	}
	(void)fclose(myFile);

	std::cout << std::endl << "Wrote image to '" + filename + "'." << std::endl;

}


glm::vec3 Camera::getAlbedo(Ray* ray) {
	std::string option = ray->objectType;

	if (option == "lambertian") {
		return glm::vec3(0.8,0.8,0.8);
	}
	else if (option == "light") {
		return glm::vec3(1.0, 1.0, 1.0);
	}
	else if (option == "mirror") {
		return glm::vec3(1.0, 1.0, 1.0);
	}
	else
	{
		return theScene->albedo;
	}


}
