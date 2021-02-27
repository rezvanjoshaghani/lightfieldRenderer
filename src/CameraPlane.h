#pragma once

#include <vector>

class CameraPlane
{
private:
	unsigned int m_rows;
	unsigned int m_cols;
	unsigned int m_gap;
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_cellWidth;
	unsigned int m_cellHeight;



public:
	CameraPlane(unsigned int rows, unsigned int cols, unsigned int gap, unsigned int width, unsigned int height);

	std::vector<int> get4NeighbouringCameras(float x, float y);

	bool isInGap(float x, float y);

};

