#include <SFML/Graphics.hpp>
#include "Mandelbrot.h"
#include <thread>
#include <iostream>


unsigned int WIDTH = 1920, HEIGHT = 1200;




int main()
{
	std::cout << "\nThis machine supports " << std::thread::hardware_concurrency() << " threads\n\n";

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mandelbrot mANdElBroT");
	Mandelbrot m(WIDTH,HEIGHT);
	


	bool restart, pause = false, loadedFromFile = m.loadLocationsFromFile("locations.txt");
	auto& interestingLocations = m.getInterestingLocations();
	while (window.isOpen())
	{
		restart = false;
		m.moveToCenter();

		if (loadedFromFile)
		{
			window.clear();
			window.draw(m.currentFrame());
			window.display();

			std::cout << "Choose one of " << interestingLocations.size() << " locations: ";
			int l;
			std::cin >> l;
			std::cout << "Chose max iterations: ";
			int maxIter;
			std::cin >> maxIter;
			m.zoomContinously(interestingLocations[l - 1].first, maxIter,2,0.99,1.001);
			m.saveToFile(true);
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
				m.advance();
				window.clear();
				window.draw(m.currentFrame());
				window.display();
				std::cout << "Max_iterations: ";
				std::cout << m.getCurrentIterations() << "\r";
			}
		}
	}

	

	

	return 0;
}

