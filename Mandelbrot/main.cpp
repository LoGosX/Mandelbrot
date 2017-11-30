#include <SFML/Graphics.hpp>
#include "ComplexNumber.h"
#include "MandelbrotSet.h"
#include <iostream>

unsigned int WIDTH = 1000, HEIGHT = 800;
sf::Vector2<double> RANGE{ 4,4 };
sf::Image img;
sf::Texture txt;
sf::Sprite sprite;

double DELTA_XY = 0.1;

const std::vector<sf::Vector2<double>> interestingLocations{
	{ -0.7463 , 0.1102 },
	{ -0.7453 , 0.1127 },
	{ -0.925 , 0.266 }
};

void zoom(MandelbrotSet& m, double deltaXY);
void zoom2(MandelbrotSet& m);


void updateMandelbrot(MandelbrotSet& m)
{
	auto v = m.createSet();
	for (size_t y = 0; y < HEIGHT; y++)
	{
		for (size_t x = 0; x < WIDTH; x++)
			img.setPixel(x, y, v[y*WIDTH + x].first ? sf::Color::Blue : sf::Color::Black);
	}
	txt.create(WIDTH, HEIGHT);
	txt.update(img);
	sprite.setTexture(txt);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");
	img.create(WIDTH, HEIGHT);

	MandelbrotSet m;
	m.setSize({WIDTH,HEIGHT });
	m.setRange(RANGE);
	m.setCenter(interestingLocations[2]);
	updateMandelbrot(m);
	
	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		zoom2(m);
		window.clear();
		window.draw(sprite);
		window.display();
	}

	return 0;
}

void zoom(MandelbrotSet& m, double deltaXY)
{
	RANGE -= {deltaXY, deltaXY};
	updateMandelbrot(m);
}

void zoom2(MandelbrotSet & m)
{
	auto r = m.getRange();
	r *= 0.9;
	m.setRange(r);
	updateMandelbrot(m);
}
