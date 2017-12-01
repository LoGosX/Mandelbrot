#include <SFML/Graphics.hpp>
#include "ComplexNumber.h"
#include "MandelbrotSet.h"
#include <iostream>
#include <thread>
#include <fstream>

unsigned int WIDTH = 1920, HEIGHT = 1200;
sf::Vector2<double> RANGE{ 4,4 };
sf::Sprite sprite;

std::vector < std::pair<sf::Vector2<double>, double>> interestingLocations;

void zoomDefault(MandelbrotSet& m);
void zoom(MandelbrotSet& m, double deltaXY);
void zoom2(MandelbrotSet& m);
void zoom3(MandelbrotSet& m);
bool loadLocationsFromFile(const char* filePath);


int main()
{
	std::cout << "\nThis machine supports " << std::thread::hardware_concurrency() << " threads\n\n";

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mandelbrot mANdElBroT");
	MandelbrotSet m;
	m.setSize({WIDTH,HEIGHT});
	


	bool restart, pause = false, loadedFromFile = loadLocationsFromFile("locations.txt");
	while (window.isOpen())
	{
		restart = false;
		m.setRange(RANGE);

		if (loadedFromFile)
		{
			zoomDefault(m);
			window.clear();
			window.draw(sprite);
			window.display();

			std::cout << "Choose one of " << interestingLocations.size() << " locations: ";
			int l;
			std::cin >> l;
			m.setCenter(interestingLocations[l - 1].first);
			std::cout << "Chose max iterations: ";
			int maxIter;
			std::cin >> maxIter;
			m.setMaxIterations(maxIter);
			pause = false;
		}

		while (!restart && window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::C))
					restart = true;
				if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					pause = !pause;
			}

			if (!pause)
			{
				zoom3(m);
				window.clear();
				window.draw(sprite);
				window.display();
			}
		}
	}

	

	

	return 0;
}

void zoomDefault(MandelbrotSet& m)
{
	m.setRange(m.defaultRange);
	sprite = m.createSetAndColor();
}

void zoom(MandelbrotSet& m, double deltaXY)
{
	RANGE -= {deltaXY, deltaXY};
	m.createSet();
}

void zoom2(MandelbrotSet & m)
{
	auto r = m.getRange();
	r *= 0.9;
	m.setRange(r);
	sprite = m.createSetAndColor();
}

void zoom3(MandelbrotSet & m)
{
	auto r = m.getRange();
	r *= 0.9;
	m.setRange(r);
	sprite = m.createSetParallel();
}

bool loadLocationsFromFile(const char * filePath)
{
	std::fstream file(filePath, std::ios::in | std::ios::out);
	if(!file.good())
		return false;

	std::pair<sf::Vector2<double>, double> d;
	while (file >> d.first.x >> d.first.y >> d.second)
		interestingLocations.push_back(d);
	return true;
}
