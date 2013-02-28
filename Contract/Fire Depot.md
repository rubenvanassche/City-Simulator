# Fire Depot Class

Class for building fire depots, inheritates the class Building.

## General
[Header](../src/Fire Depot.h)

Overloading : 
* << operator

## Functions

### FireDepot(Name, entrance, location)
Create a fire depot with a name(String obj).
And entrance(Point obj) and location(Point obj).

### addFireTruck(firetruck)
Add a firetruck(obj) to a fire depot.

### trucks()
Returns the amount of firetrucks(obj) in the fire depot.

### name()
Returns the name(String obj) of the fire depot.

### entrance()
Returns the entrance(Point obj) of the fire depot.

## Data Members

### trucks _list<FireTruck>_
Vector for storing all the FireTrucks(obj).

### name _string_
String(obj) to store the name of the fire depot.

### entrance _Point_
Point(obj) to store the entrance of the fire depot.
