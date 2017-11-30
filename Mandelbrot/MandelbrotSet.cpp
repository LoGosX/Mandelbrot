#include "MandelbrotSet.h"



MandelbrotSet::MandelbrotSet()
{
}


MandelbrotSet::~MandelbrotSet()
{
}

std::pair<bool, int> MandelbrotSet::isInMandelbrot(ComplexNumber complex)
{
	ComplexNumber c = complex;
	for (size_t iter = 1; iter <= maxIterations; iter++)
	{
		c = complex.squared() + c;
		if (c.squaredAbs() >= 8)
			return std::pair<bool, int>(false, iter);
	}
	return std::pair<bool, int>(true, maxIterations);
}
