/*
 * FireDepot.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Thursday 28 February 2013
 * 
 */

#include "FireDepot.h"
#include "DesignByContract.h"

std::ostream& operator<< (std::ostream& stream, FireDepot& objectDepot){
	Size size = objectDepot.getSize();
	for(int i = 0; i < size.getHeight(); i++){
		for(int j = 0; j < size.getWidth(); j++){
			stream << "F";
		}
		stream << std::endl;
	}
	stream << objectDepot.fName << std::endl;
	return stream;
}

bool FireDepot::isInitialized(){
	return this == FireDepot::fMyself;
}

FireDepot::FireDepot(std::string& name, Point& entrance, Point& location)  : Building(location){
	REQUIRE(entrance.isInitialized(), "The entrance location is not initialized properly");
	REQUIRE(location.isInitialized(), "The location is not initialized properly");

	Size size(4);

	this->setSize(size);
	fName = name;
	fEntrance = entrance;

	ENSURE(isInitialized(), "The FireDepot object is not initialized properly");
}


bool FireDepot::addFireTruck(FireTruck& truck){
	REQUIRE(this->isInitialized(), "The FireDepot object is not initialized properly");
	REQUIRE(truck.isInitialized(), "The Truck object is not initialized properly");

	fTrucks.push_back(truck);

	ENSURE(this->fTrucks.back().getName() == truck.getName(), "The FireTruck is not added");
}

 int FireDepot::getNrTrucks(){
	REQUIRE(this->isInitialized(), "The FireDepot object is not initialized properly");
	ENSURE(this->fTrucks.size() >= 0, "The returned value is not valid");

	return fTrucks.size();
}

std::string FireDepot::getName(){
	REQUIRE(this->isInitialized(), "The FireDepot object is not initialized properly");

	return fName;
}


Point FireDepot::getEntrance(){
	REQUIRE(this->isInitialized(), "The FireDepot object is not initialized properly");
	ENSURE(this->fEntrance.isInitialized(), "The Point object is not valid");

	return fEntrance;
}


