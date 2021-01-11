# RUSH HOUR

Welcome! This repository is for a C++17 implementation of the Rush Hour sliding block puzzle game.
A description of the board game can be found [here](https://www.thinkfun.com/products/rush-hour/).

The game instructions are simple, each vehicle can slide only in its normal direction of travel (forward and backward, not side-to-side). The goal is to clear a path such that the player car can escape the traffic jam via the opening on the right of the board.

The source code has been developed for academic purposes, i.e. to explore various solution algorithms and modern C++ containers in the STL. [CMake](https://cmake.org/) files are provided to assist building the code. Currently, it is setup for a Linux build, but this can be simply extended to Windows or Mac, if desired. It is provided as free & open-source software.

## Table of Contents

* [Prerequisites](#prerequisites)
* [Build and Run Demo](#build-and-run-demo)
* [Additional Notes](#additional-notes)

## Prerequisites

* A compiler that supports C++17
* [CMake](https://cmake.org/) Version 3.13.4 (or later)

## Build and Run AI Demo

### Linux Build

In the parent directory containing the *CMakeLists.txt* file:
```console
mkdir build
cd build
```

The directory structure is now:
```console
RUSHHOUR/
├── build/
├── cmddemo/
│   └── CMakeLists.txt
├── cppsrc/
│   └── CMakeLists.txt
├── sample_boards/
│   └── README.md
├── .gitignore
├── CMakeLists.txt
├── LICENSE
└── README.md
```

In the ```build/``` directory
```console
cmake .. && make
```

### Run Demo

Three search algorithms are provided:
* A* search
* Breadth-first search
* Depth-first search

Additionally, the demo version application can be run in three ways:
* default mode
* command line string representing the board configuration
* text file holding the board configuration

Generally, a run command from the ```build``` directory has the structure
```console
./cmddemo/rush_hour.x <command> <option1>
```
where ```command``` can be
* print
* done
* file
* next
* random
* astar
* bfs
* bfs_as_astar
* dfs

Note, if ```option1``` is left blank the default board, which is hard-coded, is used for all commands with the exception of ```file```. This is mainly in place for testing purposes.

#### print

The ```print``` command prints the initial board configuration to the terminal. For example

```console
./cmddemo/rush_hour.x print
```
```console
Board configuration:
 ------ 
|  o aa|
|  o   |
|xxo    
|ppp  q|
|     q|
|     q|
 ------
```
and
```console
./cmddemo/rush_hour.x print "  ooo |ppp q |xx  qa|rrr qa|b c dd|b c ee"
```
```console
Board configuration:
 ------ 
|  ooo |
|ppp q |
|xx  qa 
|rrr qa|
|b c dd|
|b c ee|
 ------
```

#### done

The ```done``` command is used to identify if an initial board configuration is in a solution state. For example
```console
./cmddemo/rush_hour.x done
```
```console
Board configuration:
 ------ 
|  o aa|
|  o   |
|xxo    
|ppp  q|
|     q|
|     q|
 ------
Solution state? false
```
and
```console
./cmddemo/rush_hour.x done "  oaa |  o   |  o xx|  pppq|     q|     q"
```
```console
Board configuration:
 ------ 
|  oaa |
|  o   |
|  o xx 
|  pppq|
|     q|
|     q|
 ------
Solution state? true
```

#### file

The ```file``` command is a special command that is used to read a file that contains an input board configuration and then perform some action. Use of the ```file``` command requires the form
```console
./cmddemo/rush_hour.x file <path/location> <command>
```
```path/location``` is the relative path from the build folder to the text file containing the board configuration, or an absolute path on the user system. Sample board configurations are supplied in the ```sample_boards/``` directory.

```command``` can be any of the commands listed above, with the exception of ```file``` (for obvious reasons).

#### next

The ```next``` command prints all the possible next board states from the initial board state. That is, the set of possible board states that can be reached from the given board state with a  single movement of a single vehicle.

#### random

The ```random``` command provides a random walk through the next board states. It
* generates all moves that can be generated can be reached from the given board state with a  single movement of a single vehicle
* selects one at random
* executes that move
* stops if the goal state is reached OR if it has executed 10 moves, otherwise, it repeats.

It is hard coded for 10 moves, but this can be easily modified, if desired.

#### astar

The ```astar``` command performs an A* search for a solution. It will either find a solution, print the number of moves it explored whilst searching for the solution, and print the solution path, OR it will fail to find a solution and print the number of moves it explored whilst searching for the solution. An example of an A* run using a sample board is
```console
./cmddemo/rush_hour.x file ../sample_boards/sample5.txt astar
```
```console
Board configuration:
 ------ 
|paaq  |
|p  q  |
|pxxq   
|b    o|
|bcc  o|
|  rrro|
 ------
            
Solution found!
9 moves explored.
Solution path:
 ------   ------   ------   ------  
|paaq  | |paaq  | |paa   | |paa   | 
|p  q  | |p  q  | |p     | |p     | 
|pxxq    |pxxq    |pxx     |p   xx  
|b    o| |b    o| |b  q o| |b  q o| 
|bcc  o| |bcc  o| |bccq o| |bccq o| 
|  rrro| |rrr  o| |rrrq o| |rrrq o| 
 ------   ------   ------   ------  
```
The A* routine uses a combination of the manhattan distance and the number of vehicles blocking the player vehicle from exiting the board as its heuristic function.

#### bfs

The ```bfs``` command performs a breadth-first search for a solution. It will either find a solution, print the number of moves it explored whilst searching for the solution, and print the solution path, OR it will fail to find a solution and print the number of moves it explored whilst searching for the solution. 

#### bfs_as_astar

The ```bfs_as_astar``` command performs a breadth-first search for a solution. It calls the A* search algorithm with a heuristic function == 0. It will either find a solution, print the number of moves it explored whilst searching for the solution, and print the solution path, OR it will fail to find a solution and print the number of moves it explored whilst searching for the solution. This is provide to demonstrate the relationship between breadth-first search and A*.

#### dfs

The ```dfs``` command performs a depth-first search for a solution. It will either find a solution, print the number of moves it explored whilst searching for the solution, and print the solution path, OR it will fail to find a solution and print the number of moves it explored whilst searching for the solution. 

### Using a Command Line String to Represent the Board

The code can be run using a string on the command line to represent the board. For example
```console
./cmddemo/rush_hour.x random "  oaa |  o   |  oxx |  pppq|     q|     q"
```
Note the string is provided in ```" "```. The ```|``` represent new rows and are not provided at the beginning and end of the string. All rows must be the same width (including spaces). The code will automatically deduce the exit row from the row containing the player vehicle (denoted by ```'x'```).

## Additional Notes

This code is provided free and open source for educational purposes. The code is optimized for learning and not necessarily for efficiency or compactness. It is solely the work of the author.
