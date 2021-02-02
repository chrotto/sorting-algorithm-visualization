# Sorting Algorithm Visualization
This project visualizes various sorting algorithms graphically by highlighting specific operations like array element comparisons. It lets you specify the array size and structure (e.g. unsorted or sorted) for the algorithms to sort.
It is also possible to specifiy a delay to run it slower or faster. All sorting algorithms run at the same time each in its own thread.

## Development
Currently only a solution file for **Visual Studio** is provided for an easy setup and start for development. 

For usage with another IDE or compiler you have to manually setup the include and linking directories for now.
* Project include directory is the **include/** directory in the project root
* All source files can be found in the **src/** folder in the project root
* All dependencies can be found in the **libraries/** directory which are also listed below. Take a look at each documentation to find out how to set them up.
  * SFML
  * ImGui
  * ImGui-SFML
* For compilation use the C++14 standard

A **CMake** setup will follow in the future.