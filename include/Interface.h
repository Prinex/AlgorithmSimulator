#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

// clearing the screen on windows, linux and macOS
#ifdef _WIN64
	#define clear_console() std::system("cls")
#elif defined(__linux__) || defined(__APPLE__)
	#define clear_console() std::system("clear")
#else
	std::cerr << "The current OS is unsupported." << std::endl;
#endif


#include "Algorithms.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/String.hpp>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <vector>
#include <string>
#include <memory>
#include <cmath>
#include <algorithm>


// NOTE: sf:: prefix is SFML and everything after it are defined in the SFML/... .hpp files 

/** Button class 
 *  Will allow us to create a button (a shape with text) 
 */
class Button
{
protected:
	sf::Text text;					// the text which will be place in the button
	sf::RectangleShape button;		// a rectangle object
	// bools for detecting grid's cells for start and end point and obstacles (simple cells)
	bool wall = false;
	bool startPoint = false;
	bool endPoint = false;
public:
	// Button default constructor
	Button();
	/** Button is a class constructor which will initialize and design a button
	 *  @param txt - a string for the button description
	 *  @param txtColor - a color of type sf::Color object in rgb format
	 *  @param shapeColor - the color of the rectangle
	 *  @param shapeSize - a vector containing the size of the rectangle (width, height) 
	 */
	Button(std::string txt, sf::Color txtColor, int txtSize, sf::Color shapeColor, sf::Vector2f shapeSize);

	/** Another constructor that will allow us to create simple square objects for creating a grid
	 *  that works with the pathfinding algorithms
	 *  @param shapeColor - the color of the rectangle
	 *  @param shapeSize - a vector containing the size of the rectangle (width, height) 
	 */
	Button(sf::Color shapeColor, sf::Vector2f shapeSize);

	/** Positionate method will set the position on (x, y) axis
	 *  @param size - a vector consisting of 2 float numbers
	 */
	void Positionate(sf::Vector2f size);

	/** SetShapeColor, SetTextColor will set the shape colors
	 *  @param color - a color in rgb format (r, g, b)
	 */
	void SetShapeColor(sf::Color color);
	
	void SetTextColor(sf::Color color);

	/** SetFont will set the text font 
	 *  @param font - a font e.g. arial
	 */
	void SetFont(sf::Font& font);

	/** DetectButton() - detects button when hoovering over it
	 *  @param window - a referenced object to the first initialization of the window object
	 *  @return true if mouse over button detected, false otherwise
	 */
	bool DetectButton(sf::RenderWindow& window);

	/** GetButton() - getter method for accessing the button
	 *  @return a string containing the button's text 
	 */
	sf::String GetButton() const;

	/** SetButton() - Changes the button's text and repositionate it
	 *  @param str - a constant referenced string
	 */
	void SetButton(const sf::String& str);

	/** Setter and Getter methods for wall, startPoint, and endPoint attributes 
	 *  used for configuring particular cells as a wall / obstacle, and a start or end point
	 *  on the grid
	 */
	void SetWall(bool w);

	bool GetWall() const;

	void SetStartPoint(bool s);

	bool GetStartPoint() const;

	void SetEndPoint(bool e);

	bool GetEndPoint() const;

	/** Draw draws the button on the screen
	 *  @param window - a referenced object to the first initialization of the window object
	 */
	void Draw(sf::RenderWindow& window);
};


/** Class Interface 
 *  Contains the functionlaties of the window 
 */
class Interface
{
protected:
	sf::RenderWindow window;	// window object which will be initialized only once
	sf::Font font;
	sf::Text hint;
	
	// Buttons for the configuration of sorting algorithms bar which will help us to generate, sort and print the sequence
	Button clrScrB;				// clears the screen
	Button generateSeqB;		// generates a sequence
	Button sortAlgB;			// sorts a sequence
	Button resetConfigB;		// reset the config bar
	Button increaseMinB;		// increase the minimum range of the sequence
	Button increaseMaxB;		// increase the maximum range of the sequence
	Button outputMinB;			// output for increase min
	Button outputMaxB;			// output for increase max
	Button plusElsB;			// increase for how many units to generate
	Button minusElsB;			// decrease for how many units to generate
	Button outputElsB;			// output for the number of units

	// integers for min, max and the number of units for the sorting algorithms configuration bar / GUI
	int inputMin;
	int inputMax;
	int inputEls;

	// we need a data structure for the coordinates of the start and end points
	// right heres

	// Buttons for the configuration bar of pathfinding algorithms which will help us to find the shortest path 
	// on the grid and clear the grid
	Button set;
	Button visualize;
	Button resetGrid;

	std::string algorithmType;		// will help us with the menu and navigating feature
	sf::String selectedAlg;			// same as algorithmType
	// generateSeq object (parent class) will initialize the algorithm type object (a child class)
	std::shared_ptr<SortingAlgorithms> generateSeq;	
	// generateGrid object (parent class) will initialize the algorithm type object (a child class)
	std::shared_ptr<PathFindingAlgorithms> generateGrid;
	std::vector<std::vector<Button>> grid;				// a vector which will be the grid used for pathfinding algorithms, 
														// to configure it for a specific pathfinding algorithm
	std::vector<Button> menuButtons;					// a vector containing the menu buttons
	std::vector<Button> configButtonsSortingAlgs;		// vector for configuration bar buttons of sorting algorithms
	std::vector<Button> configButtonsPathFindingAlgs;	// vector for configuration bar buttons of pathfinding algorithms
	std::vector<Button> sortingAlgsButtons;				// vector for sorting algorithms menu
	std::vector<Button> pathAlgsButtons;				// vector for pathfinding algorithms menu

public:
	// Interface default constructor
	Interface();
	/** Init method initializes the window within the main loop 	
	 *  @param init - a referenced object to the first initialization of the window object
	 *  @return back where it was called last time (menu feature / navigating)
	 */
	int Init(std::unique_ptr<Interface>& init);
	/** SortingAlgMenu initializes the sorting algorithms menu and its buttons
	 *  @param init - a referenced object to the first initialization of the window object
	 *  @return back where it was called last time (menu feature / navigating)
	 */
	int SortingAlgMenu(std::unique_ptr<Interface>& init);
	/** PathAlgMenu initializes the pathfinding algorithms menu and its buttons
	 *  @param init - a referenced object to the first initialization of the window object
	 *  @return back where it was called last time (menu feature / navigating)
	 */
	int PathAlgMenu(std::unique_ptr<Interface>& init);
	/** ConfigBar initializes the configuration bar and its menu buttons
	 *  @param init - a referenced object to the first initialization of the window object
	 *  @return back where it was called last time (menu feature / navigating)
	 */
	int ConfigBar(std::unique_ptr<Interface>& init);
	/** ConfigGrid will allow us to configure the grid for an algorithm specified
	 *	It will allow us to select a start and an end point for a pathfinding algorithm
	 *	and to place obstacles
	 *	@param init - a referenced object to the first initialization of the window object
	 *  @param initGrid - a referenced object used to the initialized grid used for making different 
	 *	configuration for the pathfinding algorithms
	 *	@return back where it was called last time (menu feature / navigating)
	 */
	int ConfigGrid(std::unique_ptr<Interface>& init);
	/** SetGrid will allow us to configured grid for an algorithm specified
	 *  @param init - a referenced object to the first initialization of the window object
	 *  @return back where it was called last time (menu feature / navigating)
	 */
	int SetGrid(std::unique_ptr<Interface>& init);
};




#endif // INTERFACE_H_INCLUDED
