![passing-win](https://img.shields.io/badge/Visual%20Studio%2017%202022%20Windows%20build-passing-green?style=plastic&logo=appveyor) ![passing-unix](https://img.shields.io/badge/Unix%20Makefiles%20Linux%20and%20macOS%20build-passing-green?style=plastic&logo=appveyor)

> AlgorithmSimulator is a cross-platform project for visualizing sorting and pathfinding algorithms.
> This project consists of two majors parts: One part of the project deals with sorting algorithms and another with pathfinding algorithms.

### Beforehand

* You need to:

1. To have VS {your installed version} installed to generate and build the project if your machine has Windows running (of course that you can try to make it work with something else like MinGW makefiles for building and running the project).
2. To have cmake 3.15 version or greater installed.
3. To have Git Bash or Linux terminal on Windows to run the Shell script files. On Linux and macOS you can run them without any problem (Unix-like systems).


### Building and running the project 

1. Before building and running the project you first need to setup SFML which is the library used for implementing graphics. 
To do this, run the setupSFML.sh script file which will extract the library's directory to the current path. 
2. To generate and build the project you will use the build.sh script file which will automatically build the project according to one of the following OS' that you use on your machine:
	* Windows
		* On Windows the build option of the project should be something like Visual Studio {a version number} {your installed version}.
	* Linux 
		* On Linux we use Unix Makefiles as the generator of the project.
	* macOS
		* On macOS, again we use Makefiles as the project's generator.
3. To run the project without any minor complications, use the run.sh script file.
	* On Window you can also run the project using VS {your installed version} IDE, but before you do that you need to do the following things: run the run.sh script file, then in VS {your installed version} solution explorer right click on 'AlgorithmSimulator' project -> select 'Set as Startup Project', then finally right-click on 'ALL_BUILD' project -> select 'Build'.  

### GUI for the Sorting Algorithms

![SAlgs](/media/generalDemo.gif)

* Navigating the interface consists in pressing left click when choosing a certain option which will keep advancing in the simulation's interface 'esc' key for going backwards.

* Instructions and notes for the GUI of the sorting algorithms
	* Only the mouse (left and right click) is used to interact with the interface in general.
	* The bar showed in the above demo includes:
		* Buttons for generating and sorting a sequence of rectangles units.
		* A button for resetting changes made.
		* Buttons for increasing / decreasing the minimum and maximum numbers between which the sequence of rectangles of different heights will be generated.
		* The green block represents the minimum height of a rectangle unit that can be generated and the red block the maximum height.
		* Buttons for increasing / decreasing the number of units to be generated.
		* The orange block represents the number of rectangle units.

#### Sorting Algorithms demos

* Bubble Sort (Left) and Slection Sort (Right)
 
![Bubble Sort](/media/bubbleSortDemo.gif) ![Selection Sort](/media/selectionSortDemo.gif)

* Insertion Sort (Left) and Merge Sort (Right)

![Insertion Sort](/media/insertionSortDemo.gif) ![Merge Sort](/media/mergeSortDemo.gif)

* Quick Sort (Left) and Heap Sort (Right)

![Quick Sort](/media/quickSortDemo.gif) ![Heap Sort](/media/heapSortDemo.gif)


### GUI for the Pathfinding Algorithms

![PAlgs](/media/palgsguiDemo.gif)

* Instructions and notes for the GUI of the pathfinding algorithms
	* Using a grid for these algorithms will allow us to place the start and end point, as well as obstacles.
	* The bar showed in the above demo includes:
		* Buttons for setting a grid and generating the shortest path.
		* A button for resetting changes made.
	* Before visualizing any algorithm you need to:
		* Set the grid
		* And then Visualize
	* To place the startpoint you need to press 's' key and left click.
	* To place the endpoint you need to press 'e' key and right click.
	* To remove the start and end point do the same thing as described above.
	* To place obstacles, press left click on any block.

#### Pathfinding Algorithms demos

* A* algorithm
 
![A*](/media/astarDemo.gif)

* Dijkstra

![Dijkstra](/media/dijkDemo.gif) 

* Breadth First Search (BFS)

![BFS](/media/bfsDemo.gif)

* Depth First Search (DFS)

![DFS](/media/dfsDemo.gif)
