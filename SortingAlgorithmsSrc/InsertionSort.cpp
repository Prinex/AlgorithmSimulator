#include "include/SortingAlgorithms.h"
#include "include/Interface.h"

InsertionSort::InsertionSort(int min, int max, int els, sf::RenderWindow& win) :
	SortingAlgorithms(min, max, els, win)
{}


int InsertionSort::Sort(std::unique_ptr<Interface>& init)
{
	while (window.isOpen())
	{
		std::vector<sf::RectangleShape>::iterator iti;
		// 64 integer size for avoiding overflowing
		unsigned long long int j;
		sf::RectangleShape leftmost;
		float xs, ys, xl, yl;
		float xs_n, ys_n;
		for (iti = sequence.begin() + 1; iti != sequence.end(); iti = std::next(iti))
		{
			leftmost = *iti;
			j = std::distance(sequence.begin(), std::prev(iti));

			// hoovering effect
			(*iti).setFillColor(sf::Color::Green);


			// swapping j elements that are greater than the current leftmost value and the rectangle's (x, y) axis
			while (j >= 0 && sequence.at(j).getSize().y > leftmost.getSize().y)
			{
				// hoovering effect
				sequence.at(j).setFillColor(sf::Color::Red);
				sequence.at(j + 1).setFillColor(sf::Color::Red);
				(*iti).setFillColor(sf::Color::Green);

				// printing & updating the screen
				window.clear(sf::Color::White);
				for (std::vector<sf::RectangleShape>::iterator itp = sequence.begin(); itp != sequence.end(); itp = std::next(itp))
				{
					if (IsSorted() != true) std::cout << (*itp).getSize().y << " ";
					window.draw(*itp);
				}
				if (IsSorted() != true) std::cout << std::endl;
				window.display();


				// hoovering effect reset
				(*iti).setFillColor(sf::Color::Black);
				sequence.at(j).setFillColor(sf::Color::Black);
				sequence.at(j + 1).setFillColor(sf::Color::Black);

				xs_n = sequence.at(j + 1).getPosition().x;
				ys_n = sequence.at(j + 1).getPosition().y;
				xs = sequence.at(j).getPosition().x;
				ys = sequence.at(j).getPosition().y;

				sequence.at(j + 1).setPosition(sf::Vector2f(xs, ys));
				sequence.at(j).setPosition(sf::Vector2f(xs_n, ys_n));

				// actual swapping
				sf::RectangleShape temp = sequence.at(j + 1);
				sequence.at(j + 1) = sequence.at(j);
				sequence.at(j) = temp;
				--j;
			}
			xl = sequence.at(j + 1).getPosition().x;
			yl = sequence.at(j + 1).getPosition().y;
			sequence.at(j + 1) = leftmost;
			sequence.at(j + 1).setPosition(sf::Vector2f(xl, yl));
		}
		return PrintSortedSeq(init);
	}
	return 0;
}