#pragma once
#include "ComplexNumber.h"
#include <vector>
#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics.hpp"

class MandelbrotSet
{
public:
	MandelbrotSet();
	~MandelbrotSet();

	std::vector<std::pair<bool, int>> points;

	const sf::Sprite& createSet();
	const sf::Sprite& createSetAndColor();
	const sf::Sprite& createSetParallel();

	void setRange(sf::Vector2<double> range);
	void setSize(sf::Vector2u size);
	void setCenter(sf::Vector2<double> center);
	sf::Vector2<double> getRange();
	void setMaxIterations(int value);
private:

	sf::Color 
		start{ sf::Color(0,0,100)}, 
		end{ sf::Color::Yellow };
	
	sf::Image img;
	sf::Texture txt;
	sf::Sprite sprite;

	sf::Vector2<double>
		range{4,4},
		center{ 0,0 };
	sf::Vector2u size{ 400,400 };
	
	int maxIterations{ 100 };
	
	std::pair<std::pair<bool, int>, ComplexNumber> isInMandelbrot(ComplexNumber complex) const;
	void colorImage();
	void createAndColorPart(std::pair<int, int> indexes, sf::Vector2<double> step);
};

