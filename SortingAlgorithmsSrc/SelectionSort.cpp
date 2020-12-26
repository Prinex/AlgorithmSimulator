#include "include/SortingAlgorithms.h"
#include "include/Interface.h"

SelectionSort::SelectionSort(int min, int max, int els, sf::RenderWindow& win) :
	SortingAlgorithms(min, max, els, win)
{}

int SelectionSort::Sort(std::unique_ptr<Interface>& init)
{
	std::vector<sf::RectangleShape>::iterator min;

	while (window.isOpen())
	{
		for (std::vector<sf::RectangleShape>::iterator iti = sequence.begin(); iti != sequence.end(); iti = std::next(iti))
		{
			// hoovering effect 1
			(*iti).setFillColor(sf::Color::Red);
			min = iti;

			// inner loop for unsorted elements 
			for (std::vector<sf::RectangleShape>::iterator itj = std::next(iti); itj != sequence.end(); itj = std::next(itj))
			{
				window.clear(sf::Color::White);
				// hoovering effect 2
				(*min).setFillColor(sf::Color::Red);
				(*itj).setFillColor(sf::Color::Red);

				// printing & updating the screen
				for (std::vector<sf::RectangleShape>::iterator itp = sequence.begin(); itp != sequence.end(); itp = std::next(itp))
				{
					if (IsSorted() != true) std::cout << (*itp).getSize().y << " ";
					window.draw(*itp);
				}
				if (IsSorted() != true) std::cout << std::endl;
				window.display();

				(*iti).setFillColor(sf::Color::Black);
				(*min).setFillColor(sf::Color::Black);
				(*itj).setFillColor(sf::Color::Black);

				// finding the next minimum element
				if ((*min).getSize().y > (*itj).getSize().y)
				{
					min = itj;
				}
			}
			// swapping elements inside vector & its axis(x, y)
			std::swap(*min, *iti);

			int x = (*min).getPosition().x;
			int y = (*min).getPosition().y;

			int xi = (*iti).getPosition().x;
			int yi = (*iti).getPosition().y;

			(*iti).setPosition(sf::Vector2f(x, y));
			(*min).setPosition(sf::Vector2f(xi, yi));
		}
		return PrintSortedSeq(init);
	}
	return 0;
}