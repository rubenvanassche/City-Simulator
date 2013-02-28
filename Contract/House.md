# House Class

Class for building houses, inheritates the class Building.

## General
[Header](../src/House.h)

Overloading : 
* << operator

## Functions

### House(location, flammability)
Creates an house with a location(Point obj) and a flammability.

### isBurning()
Checks if the house is burning.

### setFire()
Set fire to a house.

### stopFire()
Stops the fire in a house.

### flammability()
Returns the flammability of a house.

### flammability(flamability)
Change the flammabilty of a house.

## Data Members

### burns _bool_
Keep track if a house is burning

### flammability _int_
Stores the flammability of a house.