#include "include/SortingAlgorithms.h"
#include "include/Interface.h"

MergeSort::MergeSort(int min, int max, int els, sf::RenderWindow& win) :
    SortingAlgorithms(min, max, els, win)
{}


int MergeSort::Sort(std::unique_ptr<Interface>& init)
{
    return this->MSort(init, 0, sequence.size() - 1);
}


int MergeSort::MSort(std::unique_ptr<Interface>& init, unsigned long long int first, unsigned long long int last)
{
    // run between [first, last)
    if (first < last)
    {
        // find the middle index
        unsigned long long int mid = (int)floor((first + last) / 2);
        MSort(init, first, mid);
        MSort(init, mid + 1, last);
        Merge(init, first, mid, last);
    }
    return 0;
}


int MergeSort::Merge(std::unique_ptr<Interface>& init, unsigned long long int first, unsigned long long int mid, unsigned long long int last)
{
    // (i, j) - index for right and left hand side of the vector
    // k - index for the whole sequence
    int i, j, k;
    // find the size of the left side and right side of the vector
    // the index indices from before the the mid are lower
    int ls = mid - first + 1;
    // the index indices from the mid are bigger
    int rs = last - mid;
    // rectangles coordinates 
    int xk, yk;

    // left and right part of the sequence
    std::vector<sf::RectangleShape> leftSeq(ls);
    std::vector<sf::RectangleShape> rightSeq(rs);

    // separating the vector in two different vectors
    for (i = 0; i < ls; i++)
        leftSeq.at(i) = sequence.at(first + i);
    for (j = 0; j < rs; j++)
        rightSeq.at(j) = sequence.at(mid + 1 + j);


    i = 0;
    j = 0;
    k = first;

    // merging
    while (i < ls && j < rs)
    {
        // updating rectangles coordinates
        xk = sequence.at(k).getPosition().x;
        yk = sequence.at(k).getPosition().y;

        if (leftSeq.at(i).getSize().y <= rightSeq.at(j).getSize().y)
        {
            // changing rectangles coordinates and elements
            sequence.at(k) = leftSeq.at(i);
            sequence.at(k).setPosition(sf::Vector2f(xk, yk));
            i++;
        }
        else
        {
            // changing rectangles coordinates and elements
            sequence.at(k) = rightSeq.at(j);
            sequence.at(k).setPosition(sf::Vector2f(xk, yk));
            j++;
        }
        // hoovering effect
        sequence.at(k).setFillColor(sf::Color::Red);
        sequence.at(first).setFillColor(sf::Color::Green);
        sequence.at(mid + 1).setFillColor(sf::Color::Blue);
        sequence.at(last).setFillColor(sf::Color::Green);

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
        sequence.at(k).setFillColor(sf::Color::Black);
        sequence.at(first).setFillColor(sf::Color::Black);
        sequence.at(mid + 1).setFillColor(sf::Color::Black);
        sequence.at(last).setFillColor(sf::Color::Black);

        k++;
    }
    // adding the numbers that are left either from the left or right side of the sequence
    while (i < ls)
    {
        // updating rectangles coordinates only the left part
        xk = sequence.at(k).getPosition().x;
        yk = sequence.at(k).getPosition().y;

        // changing rectangles coordinates and elements
        sequence.at(k) = leftSeq.at(i);
        sequence.at(k).setPosition(sf::Vector2f(xk, yk));

        // hoovering effect
        sequence.at(k).setFillColor(sf::Color::Red);
        sequence.at(first).setFillColor(sf::Color::Green);
        sequence.at(mid + 1).setFillColor(sf::Color::Blue);
        sequence.at(last).setFillColor(sf::Color::Green);

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
        sequence.at(k).setFillColor(sf::Color::Black);
        sequence.at(first).setFillColor(sf::Color::Black);
        sequence.at(mid + 1).setFillColor(sf::Color::Black);
        sequence.at(last).setFillColor(sf::Color::Black);

        i++;
        k++;
    }
    while (j < rs)
    {
        // updating rectangles coordinates only the right part
        xk = sequence.at(k).getPosition().x;
        yk = sequence.at(k).getPosition().y;

        // changing rectangles coordinates and elements
        sequence.at(k) = rightSeq.at(j);
        sequence.at(k).setPosition(sf::Vector2f(xk, yk));

        // hoovering effect
        sequence.at(k).setFillColor(sf::Color::Red);
        sequence.at(first).setFillColor(sf::Color::Green);
        sequence.at(mid + 1).setFillColor(sf::Color::Blue);
        sequence.at(last).setFillColor(sf::Color::Green);

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
        sequence.at(k).setFillColor(sf::Color::Black);
        sequence.at(first).setFillColor(sf::Color::Black);
        sequence.at(mid + 1).setFillColor(sf::Color::Black);
        sequence.at(last).setFillColor(sf::Color::Black);

        j++;
        k++;
    }
    if (IsSorted())
        return PrintSortedSeq(init);
    return 0;
}
