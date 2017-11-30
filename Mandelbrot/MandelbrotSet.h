#pragma once
#include "ComplexNumber.h"
#include <vector>
#include "SFML\System\Vector2.hpp"

class MandelbrotSet
{
public:
	MandelbrotSet();
	~MandelbrotSet();

	std::vector<std::pair<bool, int>> points;

	std::vector<std::pair<bool, int>>& createSet();

	void setRange(sf::Vector2<double> range);
	void setSize(sf::Vector2u size);
	void setCenter(sf::Vector2<double> center);
	sf::Vector2<double> getRange();

private:
	sf::Vector2<double>
		range{4,4},
		center{ 0,0 };
	sf::Vector2u size{ 400,400 };
	int maxIterations{ 100 };
	std::pair<bool,int> isInMandelbrot(ComplexNumber complex) const;
};

