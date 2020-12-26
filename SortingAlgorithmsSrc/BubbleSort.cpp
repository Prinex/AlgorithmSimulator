#include "include/SortingAlgorithms.h"
#include "include/Interface.h"


BubbleSort::BubbleSort(int min, int max, int els, sf::RenderWindow& win) :
	SortingAlgorithms(min, max, els, win)
{}

int BubbleSort::Sort(std::unique_ptr<Interface>& init)
{
	int sortedElement = 0;
	while (window.isOpen())
	{
		for (unsigned int i = 0; i < sequence.size(); i++)
		{
			for (std::vector<sf::RectangleShape>::iterator itj = sequence.begin(); itj != sequence.end() - 1; itj = std::next(itj))
			{
				if ((*itj).getSize().y > (*std::next(itj)).getSize().y)
				{
					// hoovering effect
					(*itj).setFillColor(sf::Color::Red);
					(*std::next(itj)).setFillColor(sf::Color::Red);

					// Swapping inside the vector
					std::swap(*itj, *std::next(itj));

					// Swapping the coordinates (x, y)
					float x = (*itj).getPosition().x;
					float y = (*itj).getPosition().y;

					float x_next = (*std::next(itj)).getPosition().x;
					float y_next = (*std::next(itj)).getPosition().y;

					(*itj).setPosition(sf::Vector2f(x_next, y_next));
					(*std::next(itj)).setPosition(sf::Vector2f(x, y));

					// Printing
					window.clear(sf::Color::White);
					for (std::vector<sf::RectangleShape>::iterator itp = sequence.begin(); itp != sequence.end(); itp = std::next(itp))
					{
						if (IsSorted() != true) std::cout << (*itp).getSize().y << " ";
						window.draw(*itp);
					}
					if (IsSorted() != true) std::cout << std::endl;
					window.display();

					// hoovering effect
					(*itj).setFillColor(sf::Color::Black);
					(*std::next(itj)).setFillColor(sf::Color::Black);
				}
			}
		}
		return PrintSortedSeq(init);
	}
	return 0;
}
