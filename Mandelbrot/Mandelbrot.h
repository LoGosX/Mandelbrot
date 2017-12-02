#pragma once
#include "MandelbrotSet.h"
#include <string>

class Mandelbrot
{
public:
	Mandelbrot(unsigned int WIDTH, unsigned int HEIGHT);
	~Mandelbrot();

	const sf::Sprite& moveToCenter(double radius = 2);
	const sf::Sprite& zoom(ComplexNumber coordinate, double radius);
	bool saveCurrentFrame(const std::string& filepath);
	bool saveToFile(bool value);
	void zoomContinously(ComplexNumber center, int startingIterations = 100, double startingRadius = 2, double zoomConstant = 0.99, double iterationConstant = 1.0);
	bool advance();
	const sf::Sprite& currentFrame();
	int getCurrentIterations();

	const std::vector < std::pair<ComplexNumber, double>>& getInterestingLocations();
	bool loadLocationsFromFile(const char* filePath);

private:
	std::string saveDirectory;
	std::vector < std::pair<ComplexNumber, double>> interestingLocations;
	MandelbrotSet set;
	sf::Sprite sprite;
	sf::Texture texture;
	bool runningZoom{ false }, save_to_file{ false };
	double
		iterationConstant,
		zoomConstant,
		currentRadius,
		currentIterations{ 100 };
	int frame{ 1 };
	sf::Vector2<double> currentCenter{ 0,0 };
};

