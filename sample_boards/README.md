# Board Requirements

The default Rush Hour board is a 6 x 6 grid; however, the code is designed such that it can be any size and have any number of cars as long as it meets all of the following requirement:
* Each board row is the same width (meaning the same number of spaces)
* The player vehicle is always oriented horizontally (the code assumes the board exit is on the right of the board)
* The player vehicle is denoted by the character 'x'
* Each board needs a player vehicle (failure to provide a player vehicle or a player vehicle that is not the correct orientation will be called out by the code)
* Each vehicle is a minimum of 2 spaces (otherwise the code will not recognize it as a vehicle) - typically, cars occupy 2 spaces and trucks (trailors) occupy 3
* Each vehicle has a unique character designator, such as 'r', 'p' or 'q' - repeated identifiers will be ignored
* Borders are not to be supplied when using a text file for the board layout. The code will automatically deduce the borders.

Review the sample boards to gain additional clarity as to the board requirements.

The default board which is hard-coded is:
```console
 ------ 
|  o aa|
|  o   |
|xxo    
|ppp  q|
|     q|
|     q|
 ------
```