# City Simulator

A city simulator for project engineering.

## Contributors
- Ruben Van Assche
- Stijn Wouters

## Functionality
- Read a city with houses, fire depots, shops, ...
- Read a file with vehicles
- Set a random building on fire
- Let a fire truck drive to a burning building
- Let a fire spread arround buildings
- Repair buildings when they have lost HP
- Start a robbery
- Let a police truck drive to a shop where there is robbery
- Write the output from the siumaltion to file

## Requirements
City Simulator can be build on any system with:
- GCC
- CMake

## Buidling
It's pretty easy to compile City Simulator, just type the following commands in the terminal:
	$ cmake CMakelists.txt
	$ make

## Running
There are 3 options to run city Simulator
1. $ ./CitySimulator *No city or vehicles loaded*
2. $ ./CitySimulator cityFile.xml *A city is loaded from cityFile.xml, no vehicles loaded*
3. $ ./CitySimulator cityFile.xml vechiclesFile.xml *A city is loaded from cityFile.xml and vehicles are loaded from vehiclesFile.xml*

In the root folder you can find city.xml and vehicles.xml, these are two default files for a city and a set of vehicles.


## Tests
For each class in City Simulator there is a corresponding test called like like the class but postfixed with _test.cpp. At this moment there is no "easy" option to run the tests. You will have to download Google Test(http://code.google.com/p/googletest/) and build it. When you compile City Simulator the Google Test(libgtest.a and libgtest_main.a) librairies should be included. For specific information about including libraries please read your compiler/linker documentation. 

## Folder Structure
- **City** *Header Files, Source Code, Test Code*
- **Output-testfiles** *Files for checking if the ouput tests are working fine*
- **XML-testfiles** *Some XML files for parsing*

## License
City Simulator is licensed under the GNU GPL license.