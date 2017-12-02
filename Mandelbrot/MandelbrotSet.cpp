#include "MandelbrotSet.h"
#include <cmath>
#include <iostream>
#include <cmath>
#include <atomic>
#include <thread>

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
	this->img.create(size.x, size.y);
}

void MandelbrotSet::setCenter(sf::Vector2<double> center)
{
	this->center = center;
}

sf::Vector2<double> MandelbrotSet::getRange()
{
	return range;
}

void MandelbrotSet::setMaxIterations(int value)
{
	maxIterations = value;
}

const sf::Image & MandelbrotSet::getImg() const
{
	return img;
}

std::pair<std::pair<bool, int>,ComplexNumber> MandelbrotSet::isInMandelbrot(ComplexNumber complex) const
{
	ComplexNumber c(0,0);
	for (int i = 1; i <= maxIterations; i++)
	{
		c = c.squared() + complex;
		if (c.squaredAbs() >= 8)
			return std::pair<std::pair<bool, int>, ComplexNumber>({ false, i }, c);
	}
	return std::pair<std::pair<bool, int>, ComplexNumber>({ true, maxIterations },c);
}


sf::Color colorLerp(sf::Color a, sf::Color b, float t)
{
	return sf::Color(
		a.r + (b.r - a.r) * t,
		a.g + (b.g - a.g) * t,
		a.b + (b.b - a.b) * t
	);
}

float smoothValue(int iter, int maxIter, ComplexNumber zn)
{
	return (iter + 1 - std::log(std::log(zn.abs())) / std::log(2)) / maxIter;
}




const sf::Image& MandelbrotSet::createSetParallel()
{
	unsigned concurentThreadsSupported = std::thread::hardware_concurrency();

	std::vector<std::thread> threads(concurentThreadsSupported);
	double stepX = range.x / static_cast<double>(size.x),
		stepY = range.y / static_cast<double>(size.y);
	int pixelsPerThread = size.x * size.y / concurentThreadsSupported;

	int currIndx = 0;
	for (int i = 0; i < concurentThreadsSupported; i++)
	{
		threads[i] = std::thread(
			&MandelbrotSet::createAndColorPart,
			this,
			std::pair<int, int>(currIndx, currIndx + pixelsPerThread),
			sf::Vector2<double>(stepX, stepY)
		);
		currIndx += pixelsPerThread;
	}

	for (auto& t : threads)
		t.join();
	return this->img;
}

void MandelbrotSet::createAndColorPart(std::pair<int,int> indexes, sf::Vector2<double> step)
{
	int startIndexY = indexes.first / size.x,
		startIndexX = indexes.first % size.x,
		endIndexY = indexes.second / size.x,
		endIndexX = indexes.second % size.x;

	while (startIndexY <= endIndexY)
	{
		while (startIndexX < size.x)
		{
			if (startIndexY == endIndexY && startIndexX == endIndexX)
				return;
			auto a = isInMandelbrot(ComplexNumber(center.x - range.x / 2 + startIndexX * step.x, center.y + range.y / 2 - startIndexY * step.y));
			sf::Color c = sf::Color::Black;
			if (!a.first.first)
				c = colorLerp(start, end, smoothValue(a.first.second, maxIterations, a.second));
			img.setPixel(startIndexX, startIndexY, c);
			startIndexX++;
		}
		startIndexX = 0;
		startIndexY++;
	}
}