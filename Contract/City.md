# City Class

The whole class!

## general

Overloading : 
* << operator

## Functions

### City(file)
Create a city based upon an XML file.

### add(fireDepot)
Add an new fire depot(obj) to the city.

### add(house)
Add an new house(obj) to the city.

### add(street)
Add an new street(obj) to the city.

### _check(house)
Check if the city is still correct, there are no overlapping houses or streets.

### calculateMap()
**Uncertain**
Calculate the with and the height of the map.

## Data Members

### width _unsigned int_
**Uncertain**
To be defined by the calculateMap() function.

### height _unsigned int_
**Uncertain**
To be defined by the calculateMap() function.

### fireDepots _vector<fireDepot>_
Vector for storing all the fire depots.

### streets _vector<street>_
Vector for storing all the streets.

### houses _vector<house>_
Vector for storing all the houses.
