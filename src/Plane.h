#pragma once

#include<vector>
#include<iostream>
#include<glm/glm.hpp>



class Plane
{

private:
	int makeIndex(int i, int j, int width);


public:
	float* positions;
	unsigned int* indices;
	float* generateVertecies(unsigned int width, unsigned int height, glm::vec3 center);
	unsigned int * generateIndecies(unsigned int width, unsigned int height);
	bool intersectPlane(glm::vec3 n, glm::vec3 p0, glm::vec3 l0, glm::vec3 l, float& t);
	glm::vec3 getIntersectionPoint(float t, glm::vec3 p0, glm::vec3 l);
};


