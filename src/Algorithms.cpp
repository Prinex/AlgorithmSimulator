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
	float xCurrPos = 8;

	for (unsigned int i = 0; i != els; i++)
	{
		int randomHeight = rand() % max + min;
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
	for (std::vector<sf::RectangleShape>::iterator itp = sequence.begin(); itp != sequence.end(); itp = std::next(itp))
	{
		std::cout << (*itp).getSize().y << " ";
	}
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
		for (std::vector<sf::RectangleShape>::iterator itp = sequence.begin(); itp != sequence.end(); itp = std::next(itp))
		{
			window.draw(*itp);
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
	for (std::vector<sf::RectangleShape>::iterator it = sequence.begin(); it != sequence.end(); it = std::next(it))
	{
		std::cout << (*it).getSize().y << " ";
	}
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
			(*it).setFillColor(sf::Color::Green);
			window.draw(*it);
		}
		if (IsSorted() != true) std::cout << std::endl;
		window.display();
	}
	return 0;
}


// PathFindingAlgorithms base class definitons 
PathFindingAlgorithms::PathFindingAlgorithms(sf::RenderWindow& win) :
	window(win),
	start(0),
	end(0)
{
	Button rect(sf::Color(193, 222, 201), sf::Vector2f(30, 30));
	int xPos = 4;
	int yPos = 70;
	int64_t countCell = 1;
	for (int i = 0; i < rows; i++)
	{
		std::vector<Button> temp;
		for (int j = 0; j < columns; j++)
		{
			temp.push_back(rect);
			temp.at(j).Positionate(sf::Vector2f(xPos, yPos));
			temp.at(j).SetWeight(countCell);
			xPos += 31;
			countCell++;
		}
		grid.push_back(temp);
		xPos = 4;
        yPos += 31;
	}
}

PathFindingAlgorithms::PathFindingAlgorithms(std::vector<std::vector<Button>> g, int64_t s, int64_t e, sf::RenderWindow& win) :
	grid(g),
	start(s),
	end(e),
	window(win)
{
}

std::tuple<uint32_t, uint32_t> PathFindingAlgorithms::FindWeight(int64_t weight)
{
	for (uint32_t i = 0; i < grid.size(); i++)
	{
		for (uint32_t j = 0; j < grid.at(i).size(); j++)
		{
			if (grid.at(i).at(j).GetWeight() == weight)
				return std::make_tuple(i, j);
		}
	}
	return std::make_tuple(-1, -1);
}

int PathFindingAlgorithms::PrintPath(std::unique_ptr<Interface>& init)
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
					return init->ConfigGrid(init);
				}
			}
		}
		window.clear(sf::Color::White);
		for (std::vector<std::vector<Button>>::iterator iti = grid.begin(); iti < grid.end(); iti = std::next(iti))
		{
			for (std::vector<Button>::iterator itj = iti->begin(); itj < iti->end(); itj = std::next(itj))
			{
				(*itj).Draw(window);
			}
		}
		window.display();
	}
	return 0;
}