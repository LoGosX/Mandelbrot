#include <SFML/Graphics.hpp>
#include "ComplexNumber.h"
#include "MandelbrotSet.h"
#include <iostream>
#include <thread>

unsigned int WIDTH = 1920, HEIGHT = 1200;
sf::Vector2<double> RANGE{ 4,4 };
sf::Sprite sprite;

double DELTA_XY = 0.1;

const std::vector<sf::Vector2<double>> interestingLocations{
	{ -0.7463 , 0.1102 },
	{ -0.7453 , 0.1127 },
	{ -0.925 , 0.266 },
	{ -0.235125 , 0.827215 },
	{ 0.2549870375144766 , -0.0005679790528465 },
	{ -0.840719 , 0.22442 },
	{ -0.0452407411 , 0.9868162204352258 },
	{ -0.8115312340458353 ,  0.2014296112433656 },
	{ 0.432539867562512 ,  0.226118675951818 }
};

void zoom(MandelbrotSet& m, double deltaXY);
void zoom2(MandelbrotSet& m);
void zoom3(MandelbrotSet& m);



int main()
{
	std::cout << "\nThis machine supports " << std::thread::hardware_concurrency() << " threads\n\n";

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");
	MandelbrotSet m;
	m.setSize({WIDTH,HEIGHT});
	m.setRange(RANGE);
	std::cout << "Choose one of " << interestingLocations.size() << " locations: ";
	int l;
	std::cin >> l;
	m.setCenter(interestingLocations[l-1]);
	std::cout << "Chose max iterations: ";
	int maxIter;
	std::cin >> maxIter;
	m.setMaxIterations(maxIter);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		zoom3(m);
		window.clear();
		window.draw(sprite);
		window.display();
	}

	return 0;
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