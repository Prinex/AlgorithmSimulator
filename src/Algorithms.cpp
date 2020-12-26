#include "include/Interface.h"
#include <algorithm>


// SortingAlgorithms base class definitons 
SortingAlgorithms::SortingAlgorithms(int min, int max, int els, sf::RenderWindow& win) :
	minimum(min),
	maximum(max),
	elements(els),
	window(win)
{
	srand(time(NULL));
	float randomHeight;
	float xCurrPos = 8;

	for (unsigned int i = 0; i != els; i++)
	{
		randomHeight = rand() % max + min;
		sf::RectangleShape unit;
		unit.setSize(sf::Vector2f(4, randomHeight));
		unit.setFillColor(sf::Color::Black);
		unit.setRotation(180);
		unit.setPosition(xCurrPos, 797);
		xCurrPos += 6;
		sequence.push_back(unit);
	}
	sequenceCpy.insert(sequenceCpy.begin(), sequence.begin(), sequence.end());
	SortSeq();
}

void SortingAlgorithms::SortSeq()
{
	for (unsigned int i = 0; i < sequenceCpy.size(); i++)
	{
		for (std::vector<sf::RectangleShape>::iterator it = sequenceCpy.begin(); it != sequenceCpy.end() - 1; it = std::next(it))
		{
			if ((*it).getSize().y > (*std::next(it)).getSize().y)
			{
				// Swapping inside the vector
				std::swap(*it, *std::next(it));

				// Swapping the coordinates (x, y)
				float x = (*it).getPosition().x;
				float y = (*it).getPosition().y;

				float x_next = (*std::next(it)).getPosition().x;
				float y_next = (*std::next(it)).getPosition().y;

				(*it).setPosition(sf::Vector2f(x_next, y_next));
				(*std::next(it)).setPosition(sf::Vector2f(x, y));
			}
		}
	}
}

int SortingAlgorithms::Print(std::unique_ptr<Interface>& init)
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					return init->ConfigBar(init);
				}
			}
		}
		window.clear(sf::Color::White);
		for (std::vector<sf::RectangleShape>::iterator it = sequence.begin(); it != sequence.end(); it = std::next(it))
		{
			window.draw(*it);
		}
		window.display();
	}
	return 0;
}

bool SortingAlgorithms::IsSorted()
{
	std::vector<float> seqYaxis;
	std::vector<float> seqYaxisCpy;

	for (auto it = sequence.begin(); it != sequence.end(); it = std::next(it))
		seqYaxis.push_back((*it).getSize().y);

	for (auto it = sequenceCpy.begin(); it != sequenceCpy.end(); it = std::next(it))
		seqYaxisCpy.push_back((*it).getSize().y);

	if (seqYaxis == seqYaxisCpy)
		return true;
	return false;
}

int SortingAlgorithms::PrintSortedSeq(std::unique_ptr<Interface>& init)
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					return init->ConfigBar(init);
				}
			}
		}
		window.clear(sf::Color::White);
		for (std::vector<sf::RectangleShape>::iterator it = sequence.begin(); it != sequence.end(); it = std::next(it))
		{
			if (IsSorted() != true) std::cout << (*it).getSize().y << " ";
			(*it).setFillColor(sf::Color::Green);
			window.draw(*it);
		}
		if (IsSorted() != true) std::cout << std::endl;
		window.display();
	}
	return 0;
}