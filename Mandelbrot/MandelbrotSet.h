#pragma once
#include "ComplexNumber.h"
#include <vector>
#include <utility>

class MandelbrotSet
{
public:
	MandelbrotSet();
	~MandelbrotSet();

	std::vector<std::pair<bool, int>> points;

private:
	std::pair<int, int> leftTop{ -2,2 }, rightBottom{ 2,-2 };
	int maxIterations{ 10 };
	std::pair<bool,int> isInMandelbrot(ComplexNumber complex);
};

