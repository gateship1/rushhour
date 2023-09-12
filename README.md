# RUSH HOUR

Welcome! This repository is for a C++17 implementation of the Rush Hour sliding block puzzle game.
A description of the board game can be found [here](https://www.thinkfun.com/products/rush-hour/).

The game instructions are simple, each vehicle can slide only in its normal direction of travel (forward and backward, not side-to-side). The goal is to clear a path such that the player car can escape the traffic jam via the opening on the right of the board.

The source code has been developed for academic purposes, i.e. to explore various solution algorithms and modern C++ containers in the STL. [CMake](https://cmake.org/) files are provided to assist building the code. It is provided as free & open-source software.

<br>

<hr>

## Table of Contents

* [Prerequisites](#prerequisites)
* [Directory Structure](#directory-structure)
* [Build and Run AI Demo](#build-and-run-ai-demo)
  * [Build From Source](#build-from-source)
  * [Build And Run AI Demo](#build-and-run-ai-demo)
* [Additional Notes](#additional-notes)

<br>

<hr>

## Prerequisites

* A compiler that supports C++17

    <details>
    <summary>Install Command</summary>
    
    - Debian / Ubuntu (g++):
        
            sudo apt update
            sudo apt install build-essential
            sudo apt-get install manpages-dev
    
    - MacOS (g++):
        
            brew install gcc
    
    - Windows (cl):

      Comes installed with Microsoft Visual Studio 2022

    </details>
    
    <br>

* [CMake 3.20+](https://cmake.org/)

    <details>
    <summary>Install Command</summary>
    
    - Debian / Ubuntu:
        
            sudo apt-get install cmake
    
    - MacOS:
        
            brew install cmake
    
    - Windows:

      Comes installed with Microsoft Visual Studio 2022

    </details>

    <br>

    <details>

    <summary>Download (alternative)</summary>
    
    Alternatively, download and install from [source](https://cmake.org/download/).
    </details>
    
    <br>

* [Ninja](https://ninja-build.org/)

    <details>
    <summary>Install Command</summary>
    
    - Debian / Ubuntu:
        
            sudo wget -qO /usr/local/bin/ninja.gz https://github.com/ninja-build/ninja/releases/latest/download/ninja-linux.zip
            sudo gunzip /usr/local/bin/ninja.gz
            sudo chmod a+x /usr/local/bin/ninja
            ninja --version
    
    - MacOS:
        
            brew install ninja
    
    - Windows:

      Comes installed with Microsoft Visual Studio 2022

    </details>
    
    <br>

* Git (required for dependency fetching)

    <details>
    <summary>Install Command</summary>
    
    - Debian / Ubuntu:
        
            sudo apt install git
    
    - MacOS:
        
            brew install git
    
    - Windows:

      A limited version (suitable for use) comes installed with Microsoft Visual Studio 2022

    </details>

    <br>

* [Googletest](https://github.com/google/googletest)\
    [Googletest](https://github.com/google/googletest) is used for generating and running tests. While this is a necessary dependency, retrieval and building is handled by the `GoogleTestHelper.cmake` file. No action is required by as this is all automated. However, because [Googletest](https://github.com/google/googletest) is cloned from its [github](https://github.com/) repository, a stable internet connection is required.


\[[toc](#table-of-contents)\]

<br>

<hr>

## Directory Structure

```console
RUSHHOUR/
├── cmake/
├── demos/
│   ├── CMakeLists.txt
│   └── cmdline/
│       └── CMakeLists.txt
├── sample_boards/
│   └── README.md
├── src/
│   ├── GameEngine/
│   │   ├── Vehicles/
│   │   │   ├── PhysicsEngine/
│   │   │   │   └── CMakeLists.txt
│   │   │   └── CMakeLists.txt
│   │   └── CMakeLists.txt
│   ├── Setup/
│   │   └── CMakeLists.txt
│   ├── Solvers/
│   │   └── CMakeLists.txt
│   └── CMakeLists.txt
├── test/
│   ├── GameEngine/
│   │   ├── Vehicles/
│   │   │   ├── PhysicsEngine/
│   │   │   │   └── CMakeLists.txt
│   │   │   └── CMakeLists.txt
│   │   └── CMakeLists.txt
│   ├── Setup/
│   │   └── CMakeLists.txt
│   ├── Solvers/
│   │   └── CMakeLists.txt
│   └── CMakeLists.txt
├── .gitignore
├── .gitmodules
├── CMakeLists.txt
├── CMakePresets.json
├── LICENSE
└── README.md
```

To review each directory and file provided in the directory structure in detail, review the following Details.

<details>

<br>

### `RUSHHOUR` directory (parent directory)

This is the `parent` directory for the project.

In addition to the directories described below, the `parent` directory contains:
  * a `.gitignore` file,
  * a `.gitmodules` file (described in more detail in the [Prelude To Madness](#prelude-to-madness) section),
  * the main (driver) `CMakeLists.txt` file,
  * a `CMakePresets.json` file (which contains each configuration / build / test preset, compiler settings, etc.), and
  * a `README.md` file that contains build instructions (i.e. **this** file).

<br>

### `cmake` directory

The `cmake` directory contains the [CMake](https://cmake.org/) include files which are used to both simplify the `CMakeLists.txt` files and to modularize the build system.

<br>

### `demos` directory

The `demos` directory contains a single `CMakeLists.txt` file and subdirectories for all of the different types of demos.

<br>

### `demos/cmdline` directory

The `cmdline` directory contains the source code for running demos of the Rush Hour Game / AI engine from the command line:

* *.hpp for C++ header files
* *.cpp for C++ source files

The `cmdline` directory contains a `CMakeLists.txt` file which handles compiling and linking for the command line demo executable.

<br>

### `sample_boards` directory

The `sample_boards` directory is where sample board layouts are kept as text files. More details regarding sample boards can be found in the [Run Command Line Demo](#run-command-line-demo) section of this README.

<br>

### `src` directory

The `src` directory is where all of the source code for the rush hour game, solvers, physics, etc. is provided:

* *.hpp for C++ header files
* *.cpp for C++ source files

The `src` directory contains a `CMakeLists.txt` file which handles compiling the engine source code into a static library. Other subdirectories are located in the `src` directory with thier own `CMakeLists.txt` files for automatic inclusion in a build.

<br>

### `test` directory

The `test` directory is where all of the source code for unit testing the rush hour game, solvers, physics, etc. is provided:

* *.hpp for C++ header files
* *.cpp for C++ source files

The test directory is constructed to mirror the `src` directory so that finding tests for associated functions / routines in the `src` directory should be relatively straightforward.

The [googletest](https://github.com/google/googletest) framework is used. It is automatically downloaded and included in the build by [CMake](https://cmake.org/).

<br>

</details>
<br>

\[[toc](#table-of-contents)\]

<br>

<hr>

## Build and Run AI Demo

### Build From Source

The project uses CMake to generate a build configuration and the Ninja generator to compile the source code (see [Prerequisites](#prerequisites)). The CMake build configuration is controlled by the supplied `CMakePresets.json` file in the ```RUSHHOUR/``` parent directory.

*NOTE: A preset must be reconfigured anytime there is a change made to the `CMakePresets.json` file which affects that preset (or a configuration from which the preset inherits). Changes to the source code do not require a preset to be reconfigured, the preset can just be directly rebuilt.*

<br>

<details>
<summary>Debian / Ubuntu / MacOS build instructions</summary>

To build a configuration, the CMake preset for that configuration must first be initialized. To view the list of available preset configurations, in the ```RUSHHOUR/``` parent directory
```console
cmake --list-presets
```

A preset configuration can then be initialized from the ```RUSHHOUR/``` parent directory
```console
cmake --preset=<preset-name>
```
where ```<preset-name>``` is one of the presets produced from the ```cmake --list-presets``` command (e.g. ```rush-hour-release-linux```).

The preset is then build from the ```RUSHHOUR/``` parnet directory
```console
cmake --build --preset=<preset-name>
```
where ```<preset-name>``` is the preset just configured.

</details>

<br>

<details>
<summary>Windows build instructions</summary>

Open the project in Visual Studio. Visual Studio will automatically generate the configurations from the detected CMake files. Select the desired configuration to run from the drop-down in the configuration ribbon.

Select ```Build rush_hour_cmdline_demo.exe``` from the <u>```B```</u>```uild``` dropdown menu.

</details>

<br>

**<u>Build artifacts</u>**

The build artifacts are produced in the ```out/build/<preset-name>``` directory, where ```<preset-name>``` is the preset built.

**<u>Build artifacts - Libraries</u>**

Library build artifacts are produced in the ```out/build/<preset-name>/lib``` directory, where ```<preset-name>``` is the preset built.

**<u>Build artifacts - Demo Executables</u>**

Demo executable build artifacts are produced in the ```out/build/<preset-name>/bin``` directory, where ```<preset-name>``` is the preset built.

</details>

\[[toc](#table-of-contents)\]

<br>

<hr>

### Run Command Line Demo

Generally, a run command from the ```out/build/<preset-name>/bin``` directory has the structure
```console
./rush_hour_cmdline_demo <command> <option1>
```
where ```command``` can be
* ```print```
* ```done```
* ```file```
* ```next```
* ```random```
* ```astar```
* ```bfs```
* ```bfs_as_astar```
* ```dfs```

and ```option1``` provides three (3) run options for the command line demo to be run, namely,
* default mode
* command line string representing the board configuration
* text file holding the board configuration

*NOTE: ```./rush_hour_cmdline_demo``` will require the addition of ```.exe``` when running in Windows.*

**<u>Run Modes</u>**

<details>
<summary>default mode</summary>

Default mode is enabled if ```option1``` is left blank.

In default mode the *default board*, which is hard-coded, is used for all commands (with the exception of ```file```, as described below).

Default mode is mainly in place for testing / demonstration purposes.

</details>

<br>

<details>
<summary>command line string representing the board configuration</summary>

The command line demo application can be run using a string on the command line to represent the board. For example
```console
./rush_hour_cmdline_demo random "  oaa |  o   |  oxx |  pppq|     q|     q"
```

*Note: The string is provided in ```" "```.*

The ```|``` represent new rows and are not provided at the beginning and end of the string.

All rows must be the same width (including spaces).

The code will automatically deduce the exit row from the row containing the player vehicle (denoted by ```'x'```).

</details>

<br>

<details>
<summary>text file holding the board configuration</summary>

The command line demo application can be run using a prestored text file representing the board configuration.

This mode is enabled with the ```file``` command, which is desribed below in greater detail.

</details>

<br>

**<u>Command Descriptions / Details</u>**

<details>
<summary>print</summary>
<br>

The ```print``` command prints the initial board configuration to the terminal. For example

```console
./rush_hour_cmdline_demo print
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
./rush_hour_cmdline_demo print "  ooo |ppp q |xx  qa|rrr qa|b c dd|b c ee"
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

</details>

<br>

<details>
<summary>done</summary>
<br>

The ```done``` command is used to identify if an initial board configuration is in a solution state. For example

```console
./rush_hour_cmdline_demo done
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
./rush_hour_cmdline_demo done "  oaa |  o   |  o xx|  pppq|     q|     q"
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

</details>

<br>

<details>
<summary>file</summary>
<br>

The ```file``` command is a special command that is used to read a file that contains an input board configuration and then perform some action. Use of the ```file``` command requires the form

```console
./rush_hour_cmdline_demo file <path/location> <command>
```

```path/location``` is the relative path from the build folder to the text file containing the board configuration, or an absolute path on the user system. Sample board configurations are supplied in the ```sample_boards/``` directory.

```command``` can be any of the commands listed above, with the exception of ```file``` (for obvious reasons).

</details>

<br>

<details>
<summary>next</summary>
<br>

The ```next``` command prints all the possible next board states from the initial board state. That is, the set of possible board states that can be reached from the given board state with a  single movement of a single vehicle.

</details>

<br>

<details>
<summary>random</summary>
<br>

The ```random``` command provides a random walk through the next board states. It
* generates all moves that can be generated can be reached from the given board state with a  single movement of a single vehicle
* selects one at random
* executes that move
* stops if the goal state is reached OR if it has executed 10 moves, otherwise, it repeats.

It is hard coded for 10 moves, but this can be easily modified, if desired.

</details>

<br>

<details>
<summary>astar</summary>
<br>

The ```astar``` command performs an A* search for a solution. It will either find a solution, print the number of moves it explored whilst searching for the solution, and print the solution path, OR it will fail to find a solution and print the number of moves it explored whilst searching for the solution. An example of an A* run using a sample board is

```console
./rush_hour_cmdline_demo file ../../../../sample_boards/sample5.txt astar
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

</details>

<br>

<details>
<summary>bfs</summary>
<br>

The ```bfs``` command performs a breadth-first search for a solution. It will either find a solution, print the number of moves it explored whilst searching for the solution, and print the solution path, OR it will fail to find a solution and print the number of moves it explored whilst searching for the solution. 

</details>

<br>

<details>
<summary>bfs_as_astar</summary>
<br>

The ```bfs_as_astar``` command performs a breadth-first search for a solution. It calls the A* search algorithm with a heuristic function == 0. It will either find a solution, print the number of moves it explored whilst searching for the solution, and print the solution path, OR it will fail to find a solution and print the number of moves it explored whilst searching for the solution. This is provide to demonstrate the relationship between breadth-first search and A*.

</details>

<br>

<details>
<summary>dfs</summary>
<br>

The ```dfs``` command performs a depth-first search for a solution. It will either find a solution, print the number of moves it explored whilst searching for the solution, and print the solution path, OR it will fail to find a solution and print the number of moves it explored whilst searching for the solution. 

</details>

<br>


\[[toc](#table-of-contents)\]

<br>

<hr>


## Additional Notes

This code is provided free and open source for educational purposes. The code is provided for learning and not necessarily optimized for efficiency or compactness. It is solely the work of the author.

\[[toc](#table-of-contents)\]

<br>
