#include "CameraPlane.h"
#include <math.h>

CameraPlane::CameraPlane(unsigned int rows, unsigned int cols, unsigned int gap, unsigned int width, unsigned int height)
	:m_rows(rows), m_cols(cols), m_gap(gap), m_width(width),m_height(height)
{
	m_cellWidth = m_width / m_cols;
	m_cellHeight = m_height / m_rows;
}

std::vector<int> CameraPlane::get4NeighbouringCameras(float x, float y)
{
	std::vector<int> cameraIndex;
	int rowIndex = floor(y / m_cellHeight);
	int colIndex = floor(x / m_cellWidth);

	unsigned int cellHorizentalMid = m_cellHeight / 2;
	unsigned int cellVerticalMid = m_cellWidth / 2;

	unsigned int xInCell = (unsigned int) floor(x) % m_cellWidth;
	unsigned int yInCell = (unsigned int)floor(y) % m_cellWidth;

	//  Q1 | Q2
	//  ---|---
	//  Q4 | Q3

	if (xInCell <= cellHorizentalMid && yInCell <= cellVerticalMid) { // quarter 1
		cameraIndex.push_back(rowIndex - 1 * colIndex - 1);
		cameraIndex.push_back(rowIndex  * colIndex - 1);
		cameraIndex.push_back(rowIndex - 1 * colIndex);
		cameraIndex.push_back(rowIndex * colIndex);

	}
	else if (xInCell > cellHorizentalMid && yInCell <= cellVerticalMid) { // quarter 2
		cameraIndex.push_back(rowIndex - 1 * colIndex + 1);
		cameraIndex.push_back(rowIndex * colIndex + 1);
		cameraIndex.push_back(rowIndex - 1 * colIndex);
		cameraIndex.push_back(rowIndex * colIndex);

	}
	else if (xInCell > cellHorizentalMid && yInCell > cellVerticalMid) { // quarter 3
		cameraIndex.push_back(rowIndex + 1 * colIndex + 1);
		cameraIndex.push_back(rowIndex * colIndex + 1);
		cameraIndex.push_back(rowIndex + 1 * colIndex);
		cameraIndex.push_back(rowIndex * colIndex);
	}
	else if (xInCell <= cellHorizentalMid && yInCell > cellVerticalMid) { // quarter 4
		cameraIndex.push_back(rowIndex + 1 * colIndex - 1);
		cameraIndex.push_back(rowIndex * colIndex - 1);
		cameraIndex.push_back(rowIndex + 1 * colIndex);
		cameraIndex.push_back(rowIndex * colIndex);
	}

	return cameraIndex;
}

bool CameraPlane::isInGap(float x, float y)
{
	int rowIndex = floor(y / m_cellHeight);
	int colIndex = floor(x / m_cellWidth);

	if ((rowIndex * m_cellHeight >= y && (rowIndex * m_cellHeight + m_gap / 2) < y)
		|| (colIndex * m_cellWidth >= x && (colIndex * m_cellWidth + m_gap / 2) < x))
		return true;

	return false;
}
