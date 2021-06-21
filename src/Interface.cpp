#include "include/Interface.h"
#include "include/SortingAlgorithms.h"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>



// Button definitions 
Button::Button()
{
}

Button::Button(std::string txt, sf::Color txtColor, int txtSize, sf::Color shapeColor, sf::Vector2f shapeSize)
{
	text.setString(txt);
	text.setColor(txtColor);
	text.setCharacterSize(txtSize);
	button.setFillColor(shapeColor);
	button.setSize(shapeSize);
}

void Button::Positionate(sf::Vector2f position)
{
	button.setPosition(position);

	float x = (position.x + button.getLocalBounds().width / 2) - (text.getLocalBounds().width / 2);
	float y = (position.y + button.getLocalBounds().height / 2.2) - (text.getLocalBounds().height / 2.2);

	text.setPosition({ x, y });
}

void Button::SetShapeColor(sf::Color color)
{
	button.setFillColor(color);
}

void Button::SetTextColor(sf::Color color)
{
	text.setColor(color);
}

void Button::SetFont(sf::Font& font)
{
	text.setFont(font);
}

bool Button::DetectButton(sf::RenderWindow& window)
{
	float mouseX = sf::Mouse::getPosition(window).x;
	float mouseY = sf::Mouse::getPosition(window).y;

	float buttonX = button.getPosition().x;
	float buttonY = button.getPosition().y;

	float buttonWidth = buttonX + button.getLocalBounds().width;
	float buttonHeight = buttonY + button.getLocalBounds().height;

	if (mouseX > buttonX&& mouseY > buttonY&& mouseX < buttonWidth && mouseY < buttonHeight)
		return true;
	return false;
}

sf::String Button::GetButton() const
{
	return text.getString();
}

void Button::SetButton(const sf::String& str)
{
	float x = (button.getPosition().x + button.getLocalBounds().width / 2) - (text.getLocalBounds().width / 2);
	float y = (button.getPosition().y + button.getLocalBounds().height / 2.2) - (text.getLocalBounds().height / 2.2);

	text.setString(str);
	text.setPosition({ x, y });
}

void Button::Draw(sf::RenderWindow& window)
{
	window.draw(button);
	window.draw(text);
}



// Interface definitions  
Interface::Interface()
{
	// finding the absolute path of the font file
	// and format it correspondingly
	std::stringstream buff;
	std::string fontPath;
	buff << std::filesystem::absolute("../design/quicksandBold.otf");
	buff >> fontPath;
	
	for (std::size_t i = 0; i < fontPath.size(); i++)
	{
		std::size_t found = fontPath.find("\\\\");
		if (found != std::string::npos)
			fontPath.replace(found, 2, "/");
		std::size_t found1 = fontPath.find('"');
		if (found1 != std::string::npos)
			fontPath.replace(found1, 1, "");
	}

	if (!font.loadFromFile(fontPath))
		std::cerr << "There's no such file" << std::endl;

	hint.setFont(font);
	hint.setString("Choose an algorithm:");
	hint.setCharacterSize(24);
	hint.setFillColor(sf::Color(61, 64, 91));
	hint.setPosition({ 10, 10 });

	// Configuration buttons
	inputMin = 0;
	inputMax = 0;
	inputEls = 0;


	generateSeqB = Button("Generate", sf::Color::Black, 15, sf::Color(42, 157, 143), { 100, 50 });
	generateSeqB.SetFont(font);
	generateSeqB.Positionate({ 270, 10 });

	sortAlgB = Button("Sort", sf::Color::Black, 15, sf::Color(42, 157, 143), { 55, 50 });
	sortAlgB.SetFont(font);
	sortAlgB.Positionate({ 370.5, 10 });

	resetConfigB = Button("Reset", sf::Color::Black, 15, sf::Color(42, 157, 143), { 55, 50 });
	resetConfigB.SetFont(font);
	resetConfigB.Positionate({ 425.5, 10 });

	increaseMinB = Button(">", sf::Color::Black, 15, sf::Color(42, 157, 143), { 50, 50 });
	increaseMinB.SetFont(font);
	increaseMinB.Positionate({ 480.5, 10 });

	outputMinB = Button(std::to_string(inputMin), sf::Color::Black, 15, sf::Color::Green, { 70, 50 });
	outputMinB.SetFont(font);
	outputMinB.Positionate({ 530.5, 10 });

	outputMaxB = Button(std::to_string(inputMax), sf::Color::Black, 15, sf::Color::Red, { 70, 50 });
	outputMaxB.SetFont(font);
	outputMaxB.Positionate({ 600.5, 10 });

	increaseMaxB = Button("<", sf::Color::Black, 15, sf::Color(42, 157, 143), { 50, 50 });
	increaseMaxB.SetFont(font);
	increaseMaxB.Positionate({ 670.5, 10 });

	plusElsB = Button("+", sf::Color::Black, 15, sf::Color(42, 157, 143), { 50, 50 });
	plusElsB.SetFont(font);
	plusElsB.Positionate({ 720.5, 10 });

	outputElsB = Button(std::to_string(inputEls), sf::Color::Black, 15, sf::Color(232, 93, 4), { 50, 50 });
	outputElsB.SetFont(font);
	outputElsB.Positionate({ 770.5, 10 });

	minusElsB = Button("-", sf::Color::Black, 15, sf::Color(42, 157, 143), { 50, 50 });
	minusElsB.SetFont(font);
	minusElsB.Positionate({ 820.5, 10 });

	configButtons.push_back(generateSeqB);
	configButtons.push_back(sortAlgB);
	configButtons.push_back(resetConfigB);
	configButtons.push_back(increaseMinB);
	configButtons.push_back(outputMinB);
	configButtons.push_back(outputMaxB);
	configButtons.push_back(increaseMaxB);
	configButtons.push_back(plusElsB);
	configButtons.push_back(outputElsB);
	configButtons.push_back(minusElsB);

	// Main menu buttons
	Button sortingAlgsB("Sorting Algorithms", sf::Color::Black, 15, sf::Color(sf::Color::White), { 200, 50 });
	sortingAlgsB.SetFont(font);
	sortingAlgsB.Positionate({ 100, 100 });

	Button pathAlgsB("Pathfinding Algorithms", sf::Color::Black, 15, sf::Color(sf::Color::White), { 200, 50 });
	pathAlgsB.SetFont(font);
	pathAlgsB.Positionate({ 100, 150 });

	menuButtons.push_back(sortingAlgsB);
	menuButtons.push_back(pathAlgsB);

	// Sorting Algorithms buttons
	Button bubbleSortB("Bubble Sort", sf::Color::Black, 10, sf::Color(sf::Color::White), { 200, 50 });
	bubbleSortB.SetFont(font);
	bubbleSortB.Positionate({ 200, 50 });

	Button selectionSortB("Selection Sort", sf::Color::Black, 12, sf::Color(sf::Color::White), { 200, 50 });
	selectionSortB.SetFont(font);
	selectionSortB.Positionate({ 200, 100 });

	Button insertionSortB("Insertion Sort", sf::Color::Black, 12, sf::Color(sf::Color::White), { 200, 50 });
	insertionSortB.SetFont(font);
	insertionSortB.Positionate({ 200, 150 });

	Button mergeSortB("Merge Sort", sf::Color::Black, 12, sf::Color(sf::Color::White), { 200, 50 });
	mergeSortB.SetFont(font);
	mergeSortB.Positionate({ 200, 200 });

	Button quickSortB("Quick Sort", sf::Color::Black, 12, sf::Color(sf::Color::White), { 200, 50 });
	quickSortB.SetFont(font);
	quickSortB.Positionate({ 200, 250 });

	Button heapSortB("Heap Sort", sf::Color::Black, 12, sf::Color(sf::Color::White), { 200, 50 });
	heapSortB.SetFont(font);
	heapSortB.Positionate({ 200, 300 });

	sortingAlgsButtons.push_back(bubbleSortB);
	sortingAlgsButtons.push_back(selectionSortB);
	sortingAlgsButtons.push_back(insertionSortB);
	sortingAlgsButtons.push_back(mergeSortB);
	sortingAlgsButtons.push_back(quickSortB);
	sortingAlgsButtons.push_back(heapSortB);

	// Pathfinding Algorithms
	Button aAsteriskAlgB("A*", sf::Color::Black, 12, sf::Color(sf::Color::White), { 200, 50 });
	aAsteriskAlgB.SetFont(font);
	aAsteriskAlgB.Positionate({ 200, 50 });

	Button dijsktraAlgB("Dijkstra", sf::Color::Black, 12, sf::Color(sf::Color::White), { 200, 50 });
	dijsktraAlgB.SetFont(font);
	dijsktraAlgB.Positionate({ 200, 100 });

	Button kruskalAlgB("Kruskal", sf::Color::Black, 12, sf::Color(sf::Color::White), { 200, 50 });
	kruskalAlgB.SetFont(font);
	kruskalAlgB.Positionate({ 200, 150 });

	Button primAlgB("Prim", sf::Color::Black, 12, sf::Color(sf::Color::White), { 200, 50 });
	primAlgB.SetFont(font);
	primAlgB.Positionate({ 200, 200 });

	Button breadthFirstAlgB("Breadth First", sf::Color::Black, 12, sf::Color(sf::Color::White), { 200, 50 });
	breadthFirstAlgB.SetFont(font);
	breadthFirstAlgB.Positionate({ 200, 250 });

	Button depthFirstAlgB("Depth First", sf::Color::Black, 12, sf::Color(sf::Color::White), { 200, 50 });
	depthFirstAlgB.SetFont(font);
	depthFirstAlgB.Positionate({ 200, 300 });

	pathAlgsButtons.push_back(aAsteriskAlgB);
	pathAlgsButtons.push_back(dijsktraAlgB);
	pathAlgsButtons.push_back(kruskalAlgB);
	pathAlgsButtons.push_back(primAlgB);
	pathAlgsButtons.push_back(breadthFirstAlgB);
	pathAlgsButtons.push_back(depthFirstAlgB);

	// Initializing the main window first and then the main loop

	window.create(sf::VideoMode(1280, 800), "AlgorithmSimulator");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
}

int Interface::Init(std::unique_ptr<Interface>& init)
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			for (std::vector<Button>::iterator it = menuButtons.begin(); it != menuButtons.end(); it = std::next(it))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
				case sf::Event::MouseMoved:
					if ((*it).DetectButton(window) == true)
					{
						(*it).SetShapeColor(sf::Color(92, 103, 125));
					}
					else
					{
						(*it).SetTextColor(sf::Color::Black);
						(*it).SetShapeColor(sf::Color::White);
					}
					break;
				case sf::Event::MouseButtonPressed:
					if ((*it).DetectButton(window) == true)
					{
						(*it).SetTextColor(sf::Color::White);
						(*it).SetShapeColor(sf::Color(51, 65, 92));
					}
					break;
				case sf::Event::MouseButtonReleased:
					if ((*it).GetButton() == "Pathfinding Algorithms" && (*it).DetectButton(window) == true)
					{
						(*it).SetTextColor(sf::Color::Black);
						(*it).SetShapeColor(sf::Color(sf::Color::White));
						algorithmType = "Pathfinding Algorithms";
						return PathAlgMenu(init);
					}
					if ((*it).GetButton() == "Sorting Algorithms" && (*it).DetectButton(window) == true)
					{
						(*it).SetTextColor(sf::Color::Black);
						(*it).SetShapeColor(sf::Color(sf::Color::White));
						algorithmType = "Sorting Algorithms";
						return SortingAlgMenu(init);
					}
				case sf::Event::KeyPressed:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					{
						exit(3);
					}
					break;
				}
			}
		}
		window.clear(sf::Color(sf::Color::White));
		for (std::vector<Button>::iterator it = menuButtons.begin(); it != menuButtons.end(); it = std::next(it))
		{
			(*it).Draw(window);
		}
		window.display();
	}
	return 0;
}

int Interface::SortingAlgMenu(std::unique_ptr<Interface>& init)
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			for (std::vector<Button>::iterator it = sortingAlgsButtons.begin(); it != sortingAlgsButtons.end(); it = std::next(it))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
				case sf::Event::MouseMoved:
					if ((*it).DetectButton(window) == true)
					{
						(*it).SetShapeColor(sf::Color(92, 103, 125));
					}
					else
					{
						(*it).SetTextColor(sf::Color::Black);
						(*it).SetShapeColor(sf::Color::White);
					}
					break;
				case sf::Event::MouseButtonPressed:
					if ((*it).DetectButton(window) == true)
					{
						(*it).SetTextColor(sf::Color::White);
						(*it).SetShapeColor(sf::Color(51, 65, 92));
					}
					break;
				case sf::Event::MouseButtonReleased:
					if ((*it).DetectButton(window) == true)
					{
						(*it).SetTextColor(sf::Color::Black);
						(*it).SetShapeColor(sf::Color(sf::Color::White));
						selectedAlg = (*it).GetButton();
						return ConfigBar(init);
					}
					break;
				case sf::Event::KeyPressed:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					{
						return Init(init);
					}
					break;
				}
			}
		}
		window.clear(sf::Color(sf::Color::White));
		window.draw(hint);
		for (std::vector<Button>::iterator it = sortingAlgsButtons.begin(); it != sortingAlgsButtons.end(); it = std::next(it))
		{
			(*it).Draw(window);
		}
		window.display();
	}
	return 0;
}

int Interface::PathAlgMenu(std::unique_ptr<Interface>& init)
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			for (std::vector<Button>::iterator it = pathAlgsButtons.begin(); it != pathAlgsButtons.end(); it = std::next(it))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
				case sf::Event::MouseMoved:
					if ((*it).DetectButton(window) == true)
					{
						(*it).SetShapeColor(sf::Color(92, 103, 125));
					}
					else
					{
						(*it).SetTextColor(sf::Color::Black);
						(*it).SetShapeColor(sf::Color::White);
					}
					break;
				case sf::Event::MouseButtonPressed:
					if ((*it).DetectButton(window) == true)
					{
						(*it).SetTextColor(sf::Color::White);
						(*it).SetShapeColor(sf::Color(51, 65, 92));
					}
					break;
				case sf::Event::MouseButtonReleased:
					if ((*it).DetectButton(window) == true)
					{
						(*it).SetTextColor(sf::Color::Black);
						(*it).SetShapeColor(sf::Color(sf::Color::White));
						selectedAlg = (*it).GetButton();
						return ConfigBar(init);
					}
					break;
				case sf::Event::KeyPressed:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					{
						return Init(init);
					}
					break;
				}
			}
		}
		window.clear(sf::Color(sf::Color::White));
		window.draw(hint);
		for (std::vector<Button>::iterator it = pathAlgsButtons.begin(); it != pathAlgsButtons.end(); it = std::next(it))
		{
			(*it).Draw(window);
		}
		window.display();
	}
	return 0;
}

int Interface::ConfigBar(std::unique_ptr<Interface>& init)
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			for (std::vector<Button>::iterator it = configButtons.begin(); it != configButtons.end(); it = std::next(it))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
				case sf::Event::MouseMoved:
					if ((*it).DetectButton(window) == true)
					{
						(*it).SetTextColor(sf::Color::White);
					}
					else
					{
						(*it).SetTextColor(sf::Color::Black);
					}
					break;
				case sf::Event::MouseButtonPressed:
					if ((*it).DetectButton(window) == true && (std::distance(configButtons.begin(), it) != 4 && std::distance(configButtons.begin(), it) != 5 && std::distance(configButtons.begin(), it) != 8))
					{
						(*it).SetShapeColor(sf::Color(0, 109, 119));
					}
					break;
				case sf::Event::MouseButtonReleased:
					if ((*it).DetectButton(window) == true && (std::distance(configButtons.begin(), it) != 4 && std::distance(configButtons.begin(), it) != 5 && std::distance(configButtons.begin(), it) != 8))
					{
						(*it).SetTextColor(sf::Color::Black);
						(*it).SetShapeColor(sf::Color(42, 157, 143));
					}
					if ((*it).DetectButton(window) == true && (*it).GetButton() == ">")
					{
						inputMin += 10;
						configButtons.at(4).SetButton(std::to_string(inputMin));
					}
					if ((*it).DetectButton(window) == true && (*it).GetButton() == "<")
					{
						inputMax += 10;
						configButtons.at(5).SetButton(std::to_string(inputMax));
					}
					if ((*it).DetectButton(window) == true && (*it).GetButton() == "+")
					{
						inputEls += 1;
						configButtons.at(8).SetButton(std::to_string(inputEls));
					}
					if ((*it).DetectButton(window) == true && (*it).GetButton() == "-")
					{
						inputEls -= 1;
						if (inputEls < 0)
						{
							inputEls = 0;
							std::cerr << "Cannot be less than 0" << std::endl;
						}
						configButtons.at(8).SetButton(std::to_string(inputEls));
					}
					if ((*it).DetectButton(window) == true && (*it).GetButton() == "Reset")
					{
						clear_console();
						if (inputMin == 0 && inputMax == 0 && inputEls == 0)
						{
							std::cerr << "There is no sequence generated" << std::endl;
							break;
						}
						inputMin = 0;
						inputMax = 0;
						inputEls = 0;
						configButtons.at(4).SetButton(std::to_string(inputMin));
						configButtons.at(5).SetButton(std::to_string(inputMax));
						configButtons.at(8).SetButton(std::to_string(inputEls));
					}
					if ((*it).DetectButton(window) == true && (*it).GetButton() == "Generate")
					{
						clear_console();
						if (inputMin == 0 || inputMax == 0 || inputEls == 0)
						{
							std::cerr << "Cannot generate a sequence by default configuration" << std::endl;
							break;
						}
						if (selectedAlg == "Bubble Sort")
						{
							generateSeq = std::make_shared<BubbleSort>(inputMin, inputMax, inputEls, window);
							return generateSeq->Print(init);
						}
						if (selectedAlg == "Selection Sort")
						{
							generateSeq = std::make_shared<SelectionSort>(inputMin, inputMax, inputEls, window);
							return generateSeq->Print(init);
						}
						if (selectedAlg == "Insertion Sort")
						{
							generateSeq = std::make_shared<InsertionSort>(inputMin, inputMax, inputEls, window);
							return generateSeq->Print(init);
						}
						if (selectedAlg == "Merge Sort")
						{
							generateSeq = std::make_shared<MergeSort>(inputMin, inputMax, inputEls, window);
							return generateSeq->Print(init);
						}
						if (selectedAlg == "Quick Sort")
						{
							generateSeq = std::make_shared<QuickSort>(inputMin, inputMax, inputEls, window);
							return generateSeq->Print(init);
						}
						if (selectedAlg == "Heap Sort")
						{
							generateSeq = std::make_shared<HeapSort>(inputMin, inputMax, inputEls, window);
							return generateSeq->Print(init);
						}
					}
					if ((*it).DetectButton(window) == true && (*it).GetButton() == "Sort")
					{
						clear_console();
						if (inputMin == 0 || inputMax == 0 || inputEls == 0)
						{
							std::cerr << "There is no sequence generated" << std::endl;
							break;
						}
						if (generateSeq->IsSorted())
						{
							std::cerr << "The sequence is already sorted" << std::endl;
							return generateSeq->PrintSortedSeq(init);
						}
						return generateSeq->Sort(init);
					}
				case sf::Event::KeyPressed:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					{
						if (algorithmType == "Sorting Algorithms")
						{
							return SortingAlgMenu(init);
						}
						return PathAlgMenu(init);
					}
					break;
				default:
					break;
				}
			}
		}
		window.clear(sf::Color(sf::Color::White));
		for (std::vector<Button>::iterator it = configButtons.begin(); it != configButtons.end(); it = std::next(it))
		{
			(*it).Draw(window);
		}
		window.display();
	}
	return 0;
}

