#include "include/SortingAlgorithms.h"
#include "include/Interface.h"

QuickSort::QuickSort(int min, int max, int els, sf::RenderWindow& win) :
	SortingAlgorithms(min, max, els, win)
{}

int QuickSort::Sort(std::unique_ptr<Interface>& init)
{
	return this->QSort(init, 0, sequence.size() - 1);
}

int QuickSort::QSort(std::unique_ptr<Interface>& init, int left, int right)
{
		int p = (left + right) / 2;
		int pivot = sequence.at(p).getSize().y;
		int l = left;
		int r = right;
		int x_l, y_l, x_r, y_r;
		while (l <= r)
		{
			while (sequence.at(l).getSize().y < pivot)
			{
				// hoovering effect
				sequence.at(l).setFillColor(sf::Color::Red);
				sequence.at(p).setFillColor(sf::Color::Green);
				sequence.at(r).setFillColor(sf::Color::Red);
				
				// Printing
				window.clear(sf::Color::White);
				for (std::vector<sf::RectangleShape>::iterator itp = sequence.begin(); itp != sequence.end(); itp = std::next(itp))
				{
					window.draw(*itp);
				}
				window.display();
				
				// hoovering effect reset
				sequence.at(l).setFillColor(sf::Color::Black);
				sequence.at(p).setFillColor(sf::Color::Black);
				sequence.at(r).setFillColor(sf::Color::Black);
				l++;
			}
			while (sequence.at(r).getSize().y > pivot)
			{
				// hoovering effect
				sequence.at(l).setFillColor(sf::Color::Red);
				sequence.at(p).setFillColor(sf::Color::Green);
				sequence.at(r).setFillColor(sf::Color::Red);
			
				// Printing
				window.clear(sf::Color::White);
				for (std::vector<sf::RectangleShape>::iterator itp = sequence.begin(); itp != sequence.end(); itp = std::next(itp))
				{
					window.draw(*itp);
				}
				window.display();
				
				// hoovering effect reset
				sequence.at(l).setFillColor(sf::Color::Black);
				sequence.at(p).setFillColor(sf::Color::Black);
				sequence.at(r).setFillColor(sf::Color::Black);
				r--;
			}
			if (l <= r)
			{
				// hoovering effect
				sequence.at(l).setFillColor(sf::Color::Magenta);
				sequence.at(p).setFillColor(sf::Color::Green);
				sequence.at(r).setFillColor(sf::Color::Magenta);
				std::swap(sequence.at(l), sequence.at(r));
				x_l = sequence.at(l).getPosition().x;
				y_l = sequence.at(l).getPosition().y;
				x_r = sequence.at(r).getPosition().x;
				y_r = sequence.at(r).getPosition().y;
				sequence.at(l).setPosition(sf::Vector2f(x_r, y_r));
				sequence.at(r).setPosition(sf::Vector2f(x_l, y_l));
				
				// Printing
				window.clear(sf::Color::White);
				for (std::vector<sf::RectangleShape>::iterator itp = sequence.begin(); itp != sequence.end(); itp = std::next(itp))
				{
					std::cout << (*itp).getSize().y << " ";
					window.draw(*itp);
				}
				std::cout << std::endl;
				window.display();
				
				// hoovering effect reset
				sequence.at(l).setFillColor(sf::Color::Black);
				sequence.at(p).setFillColor(sf::Color::Black);
				sequence.at(r).setFillColor(sf::Color::Black);

				if (p == l)
				{
					p = r;
				}
				else if (p == r)
				{
					p = l;
				}
				// hoovering effect
				sequence.at(l).setFillColor(sf::Color::Red);
				sequence.at(p).setFillColor(sf::Color::Green);
				sequence.at(r).setFillColor(sf::Color::Red);
				
				// Printing
				window.clear(sf::Color::White);
				for (std::vector<sf::RectangleShape>::iterator itp = sequence.begin(); itp != sequence.end(); itp = std::next(itp))
				{
					window.draw(*itp);
				}
				window.display();
				
				// hoovering effect reset
				sequence.at(l).setFillColor(sf::Color::Black);
				sequence.at(p).setFillColor(sf::Color::Black);
				sequence.at(r).setFillColor(sf::Color::Black);
				l++;
				r--;
			}
		}
		if (left < r)
			QSort(init, left, r);
		if (l < right)
			QSort(init, l, right);
		if (IsSorted())
			return PrintSortedSeq(init);
	return 0;
}
