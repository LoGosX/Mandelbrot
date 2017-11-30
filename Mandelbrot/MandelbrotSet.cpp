#include "MandelbrotSet.h"
#include <cmath>
#include <iostream>
#include <cmath>

MandelbrotSet::MandelbrotSet()
{
}


MandelbrotSet::~MandelbrotSet()
{
}

void MandelbrotSet::setRange(sf::Vector2<double> range)
{
	this->range = range;
	this->range.x = std::abs(this->range.x);
	this->range.y = std::abs(this->range.y);
}

void MandelbrotSet::setSize(sf::Vector2u size)
{
	this->size = size;
}

void MandelbrotSet::setCenter(sf::Vector2<double> center)
{
	this->center = center;
}

sf::Vector2<double> MandelbrotSet::getRange()
{
	return range;
}

std::pair<bool, int> MandelbrotSet::isInMandelbrot(ComplexNumber complex) const
{
	ComplexNumber c(0,0);
	for (int i = 1; i <= maxIterations; i++)
	{
		c = c.squared() + complex;
		if (c.squaredAbs() >= 8)
			return std::pair<bool, int>(false, i);
	}
	return std::pair<bool, int>(true, maxIterations);
}

std::vector<std::pair<bool, int>>& MandelbrotSet::createSet()
{
	points.resize(size.x * size.y);
	int iterX = 0, iterY = 0;
	double stepX = range.x / static_cast<double>(size.x),
		stepY = range.y / static_cast<double>(size.y);
	for (double y = center.y + range.y / 2; (y >= center.y - range.y / 2) && iterY < size.y; y -= stepY, iterY++)
	{
		for (double x = center.x - range.x / 2, iterX = 0; (x <= center.x + range.x) && iterX < size.x; x += stepX, iterX++)
			points[iterY * size.x + iterX] = (isInMandelbrot(ComplexNumber(x, y)));
		std::cout << "Creating... ";
		std::cout << static_cast<int>(std::ceil(iterY * size.x + iterX) * 100 / (size.x * size.y)) << "%\r";
	}

	return this->points;
}