#include "Mandelbrot.h"
#include <string>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <windows.h>

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

Mandelbrot::Mandelbrot(unsigned int WIDTH, unsigned int HEIGHT)
{
	texture.create(WIDTH, HEIGHT);
	set.setSize({ WIDTH,HEIGHT });
}

Mandelbrot::~Mandelbrot()
{
}

const sf::Sprite& Mandelbrot::moveToCenter(double radius)
{
	return zoom({ 0,0 }, radius);
}

const sf::Sprite& Mandelbrot::zoom(ComplexNumber coordinate, double radius)
{
	set.setCenter({ coordinate.a, coordinate.b });
	set.setRange({ radius * 2,radius * 2 });
	set.setMaxIterations(int(currentIterations));
	texture.update(set.createSetParallel());
	sprite.setTexture(texture);
	return sprite;
}

bool Mandelbrot::saveCurrentFrame(const std::string& filepath)
{
	return set.saveImageTo((filepath + std::to_string(frame++) + ".jpg").c_str());
}

bool Mandelbrot::saveToFile(bool value)
{
	return save_to_file = value;
}

void Mandelbrot::zoomContinously(ComplexNumber coordinate, int startingIterations, double startingRadius, double zoomConstant, double iterationConstant)
{
	this->currentCenter = { coordinate.a, coordinate.b };
	this->currentIterations = startingIterations;
	this->currentRadius = startingRadius;
	this->zoomConstant = zoomConstant;
	this->iterationConstant = iterationConstant;
	this->runningZoom = true;
	this->frame = 1;

	auto t = std::time(nullptr);
	auto tm = *(std::localtime(&t));
	std::ostringstream oss;
	oss << std::put_time(&tm, "%d-%m-%Y__%H-%M-%S");
	this->saveDirectory = oss.str();
	saveDirectory = "Images\\" + saveDirectory;
	system(("mkdir " + saveDirectory).c_str());
	zoom(coordinate, startingRadius);
}

bool Mandelbrot::advance()
{
	if(!runningZoom)
		return false;
	currentRadius *= zoomConstant;
	currentIterations *= iterationConstant;
	set.setMaxIterations(int(currentIterations));
	zoom({ currentCenter.x, currentCenter.y }, currentRadius);

	if (save_to_file)
		saveCurrentFrame(saveDirectory + "\\");
	return true;
}

const sf::Sprite & Mandelbrot::currentFrame()
{
	return sprite;
}

int Mandelbrot::getCurrentIterations()
{
	return currentIterations;
}

const std::vector<std::pair<ComplexNumber, double>>& Mandelbrot::getInterestingLocations()
{
	return interestingLocations;
}

bool Mandelbrot::loadLocationsFromFile(const char * filePath)
{
	std::fstream file(filePath, std::ios::in | std::ios::out);
	if (!file.good())
		return false;

	std::pair<ComplexNumber, double> d;
	while (file >> d.first.a >> d.first.b >> d.second)
		interestingLocations.push_back(d);
	file.close();
	return true;
}
