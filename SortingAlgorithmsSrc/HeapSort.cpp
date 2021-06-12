#include "include/SortingAlgorithms.h"
#include "include/Interface.h"


HeapSort::HeapSort(int min, int max, int els, sf::RenderWindow& win) :
	SortingAlgorithms(min, max, els, win)
{}

int HeapSort::Sort(std::unique_ptr<Interface>& init)
{
	return this->HSort(init, sequence.size() / 2 - 1, sequence.size());
}

int HeapSort::Heapify(std::unique_ptr<Interface>& init, int start, int end)
{
	int root = start;
	int temp = root;
	int child = 2 * root + 1;
	int x_root, y_root, x_temp, y_temp;
	if (child < end && sequence.at(temp).getSize().y < sequence.at(child).getSize().y)
	{
		// hoovering effect
		sequence.at(temp).setFillColor(sf::Color::Red);
		sequence.at(child).setFillColor(sf::Color::Red);
		
		// Printing
		window.clear(sf::Color::White);
		for (std::vector<sf::RectangleShape>::iterator itp = sequence.begin(); itp != sequence.end(); itp = std::next(itp))
		{
			window.draw(*itp);
		}
		std::cout << std::endl;
		window.display();
		
		// hoovering effect reset
		sequence.at(temp).setFillColor(sf::Color::Black);
		sequence.at(child).setFillColor(sf::Color::Black);
		temp = child;
	}
	if (child + 1 < end && sequence.at(temp).getSize().y < sequence.at(child + 1).getSize().y)
	{
		// hoovering effect
		sequence.at(temp).setFillColor(sf::Color::Red);
		sequence.at(child + 1).setFillColor(sf::Color::Red);
		
		// Printing
		window.clear(sf::Color::White);
		for (std::vector<sf::RectangleShape>::iterator itp = sequence.begin(); itp != sequence.end(); itp = std::next(itp))
		{
			window.draw(*itp);
		}
		std::cout << std::endl;
		window.display();
		
		// hoovering effect reset
		sequence.at(temp).setFillColor(sf::Color::Black);
		sequence.at(child + 1).setFillColor(sf::Color::Black);
		temp = child + 1;
	}
	if (temp != root)
	{
		// hoovering effect
		sequence.at(temp).setFillColor(sf::Color::Red);
		sequence.at(root).setFillColor(sf::Color::Red);

		// swap values the elements and its coordinates
		std::swap(sequence.at(root), sequence.at(temp));
		x_root = sequence.at(root).getPosition().x;
		y_root = sequence.at(root).getPosition().y;
		x_temp = sequence.at(temp).getPosition().x;
		y_temp = sequence.at(temp).getPosition().y;
		sequence.at(root).setPosition(sf::Vector2f(x_temp, y_temp));
		sequence.at(temp).setPosition(sf::Vector2f(x_root, y_root));

		// Printing
		window.clear(sf::Color::White);
		for (std::vector<sf::RectangleShape>::iterator itp = sequence.begin(); itp != sequence.end(); itp = std::next(itp))
		{
			if (IsSorted() != true) std::cout << (*itp).getSize().y << " ";
			window.draw(*itp);
		}
		std::cout << std::endl;
		window.display();

		// hoovering effect reset
		sequence.at(temp).setFillColor(sf::Color::Black);
		sequence.at(root).setFillColor(sf::Color::Black);
		
		Heapify(init, temp, end);
	}
	return 0;
}

int HeapSort::HSort(std::unique_ptr<Interface>& init, int start, int size)
{
	// heapify the sequence - max heap
	int x_cur, y_cur, x_first, y_first;
	for (int i = start; i >= 0; i--)
	{
		Heapify(init, i, size);
	}
	std::cout << "\nThe sequence has been heapified.\n" << std::endl;
	int end = sequence.size() - 1;
	for (int i = end; i >= 0; i--)
	{
		// hoovering effect
		sequence.at(i).setFillColor(sf::Color::Red);
		sequence.at(0).setFillColor(sf::Color::Red);

		// swap values the elements and its coordinates
		std::swap(sequence.at(i), sequence.at(0));
		x_cur = sequence.at(i).getPosition().x;
		y_cur = sequence.at(i).getPosition().y;
		x_first = sequence.at(0).getPosition().x;
		y_first = sequence.at(0).getPosition().y;
		sequence.at(i).setPosition(sf::Vector2f(x_first, y_first));
		sequence.at(0).setPosition(sf::Vector2f(x_cur, y_cur));

		// Printing
		window.clear(sf::Color::White);
		for (std::vector<sf::RectangleShape>::iterator itp = sequence.begin(); itp != sequence.end(); itp = std::next(itp))
		{
			if (IsSorted() != true) std::cout << (*itp).getSize().y << " ";
			window.draw(*itp);
		}
		std::cout << std::endl;
		window.display();

		// hoovering effect reset
		sequence.at(i).setFillColor(sf::Color::Black);
		sequence.at(0).setFillColor(sf::Color::Black);
		
		Heapify(init, 0, i);
	}
	if (IsSorted())
		return PrintSortedSeq(init);
	return 0;
}