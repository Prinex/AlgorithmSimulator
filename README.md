> AlgorithmSimulator is a cross-platform project for visualizing sorting and pathfinding algorithms.
> This project consists of two majors parts: One part of the project deals with sorting algorithms and another with pathfinding algorithms which is under processing.

### Building and running the project 

1. Before building and running the project you first need to setup SFML which is the library used for implementing the graphics. 
To do this, run the setupSFML.sh script file which will extract the library's directory to the current path. 
2. To generate and build the project you will use the build.sh script file which will automatically build the project according to one of the following OS' that you use on your machine:
	* Windows
		* On Windows the build option of the project is Visual Studio 16 2019.
		* You can also run the project using VS 2019, but before you do that you need to do the following things: run the run.sh script file, then in VS 2019 solution explorer right click on 'AlgorithmSimulator' project -> select 'Set as Startup Project', then finally right-click on 'ALL_BUILD' project -> select 'Build'. 
	* Linux 
		* On Linux we use Unix Makefiles as the generator of the project.
	* macOS
		* On macOS, again we use Makefiles as the project's generator.
3. To run the project, use the run.sh script file.

### General demo of the project's GUI

![The interface](/media/generalDemo.gif)

### Sorting Algorithms demos

* Bubble Sort and Slection Sort
 
![Bubble Sort](/media/bubbleSortDemo.gif) ![Selection Sort](/media/selectionSortDemo.gif)

* Insertion Sort and Merge Sort

![Insertion Sort](/media/insertionSortDemo.gif) ![Merge Sort](/media/mergeSortDemo.gif)

* Quick Sort and Heap Sort

![Quick Sort](/media/quickSortDemo.gif) ![Heap Sort](/media/heapSortDemo.gif)
