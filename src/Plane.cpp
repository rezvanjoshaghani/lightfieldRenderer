#include "Plane.h"


float* Plane::generateVertecies(unsigned int width, unsigned int height, glm::vec3 center)
{
	positions = new float[(width+1)*(height +1)*9];
	unsigned int k = 0;
	int mw = width / 2;
	int mh = height / 2;
	int i, j;
	for ( i = -1*mw; i < mw; i++) {
		for (j = -1*mh; j < mh; j++) {
			// 3D position
			positions[k] = j + center.x;
			positions[k + 1] = i + center.y;
			positions[k + 2] = center.z;

			// 2D texture Coordinate
			positions[k + 3] = (j + mh) * (1.0 / width);
			positions[k + 4] = (i + mw) * (1.0 / height);

			//std::cout <<"Texture coord: "<< (j + mh) * (1.0 / width) << " , " << (i + mw) * (1.0 / height) << "\n";
			//std::cout << " coord: " << j << " , " << i << "\n";

			k+=5;
		}
	}
	return positions;
}

unsigned int* Plane::generateIndecies(unsigned int width, unsigned int height)
{
	indices = new unsigned int[(width-1)*(height-1)*2*3];
	int k = 0;

	for (int i = 0; i < width - 1; i++) {
		for (int j = 0; j < height - 1; j++) {
			indices[k] = makeIndex(i, j, width);
			indices[k+1]= makeIndex(i, j+1, width);
			indices[k + 2] = makeIndex(i+1, j + 1, width);

			indices[k + 3] = makeIndex(i, j, width);
			indices[k + 4] = makeIndex(i + 1, j, width);
			indices[k + 5] = makeIndex(i + 1, j + 1, width);
			k += 6;
		}
	}

	return indices;
}


int Plane::makeIndex(int i, int j,int width) {
	return i * width + j;
}

// t=(p0-l0).n/l.n
//P0: is the point on plane
//n: plane normal
//l0: ray origin
//l: ray direction

bool Plane::intersectPlane(glm::vec3 n, glm::vec3 p0, glm::vec3 l0, glm::vec3 l, float& t)
{
	// assuming vectors are all normalized
	float denom = glm::dot(n, l);
	std::cout << "denom:" << denom << "\n";
	if (abs(denom) > 1e-6) {
		glm::vec3 p0l0 = p0 - l0;
		t = dot(p0l0, n) / denom;
		std::cout << "dist:" << t << "\n";
		return (t >= 0);
	}

	return false;
}

//P=P0+tl
glm::vec3 Plane::getIntersectionPoint(float t, glm::vec3 p0, glm::vec3 l) {

	return p0 + t * l;

}