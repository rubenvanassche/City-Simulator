/*
 * Fire.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Thursday 28 February 2013
 * 
 */

#include "Fire.h"
#include "DesignByContract.h"

std::ostream& operator<< (std::ostream& stream, FireDepot& objectDepot){
/*	Size size = *objectDepot.getSize();
	for(int i = 0; i < *size.getHeight(); i++){
		for(int j = 0; j < *size.getWidth(); j++){
			stream << "F";
		}
		stream << std::endl;
	}
	stream << objectDepot.fName << std::endl;
*/	return stream;
}

bool FireDepot::isInitialized(){
	return this == FireDepot::fMyself;
}

FireDepot::FireDepot(std::string& name, Point& entrance, Point& location)  : Building(location){
	REQUIRE(entrance.isInitialized(), "The entrance location is not initialized properly");
	REQUIRE(location.isInitialized(), "The location is not initialized properly");

	Size size(4);
	this->setSize(size);
	FireDepot::fName = name;
	FireDepot::fEntrance = entrance;
	FireDepot::fMyself = this;

	ENSURE(isInitialized(), "The FireDepot object is not initialized properly");
}


bool FireDepot::addFireTruck(FireTruck& truck){
	REQUIRE(this->isInitialized(), "The FireDepot object is not initialized properly");
	REQUIRE(truck.isInitialized(), "The Truck object is not initialized properly");

	FireDepot::fTrucks.push_back(truck);

	ENSURE(*(this->fTrucks.back().getName()) == *truck.getName(), "The FireTruck is not added");
	return true;
}

int FireDepot::getNrTrucks(){
	REQUIRE(this->isInitialized(), "The FireDepot object is not initialized properly");
	return FireDepot::fTrucks.size();
}

std::string* FireDepot::getName(){
	REQUIRE(this->isInitialized(), "The FireDepot object is not initialized properly");
	return &(FireDepot::fName);
}

Point* FireDepot::getEntrance(){
	REQUIRE(this->isInitialized(), "The FireDepot object is not initialized properly");
	return &(FireDepot::fEntrance);
}

std::ostream& operator<< (std::ostream& stream, FireTruck& firetruck) {
	stream << "FireTruck " << *firetruck.getName() << std::endl;
	stream << "\t" << "base: " << *(firetruck.getBase()->getName()) << " "
			<< *(firetruck.getBase()->getLocation()) << std::endl;
	stream << "\t" << "On his way to " << *(firetruck.getDestination()) << std::endl;
	stream << "\t" << "Now on " << *(firetruck.getPosition()) << std::endl;
	return stream;
}


bool FireTruck::isInitialized() {
	return FireTruck::fMyself == this;
}

FireTruck::FireTruck(Point& cur_pos, Point& destination, std::string& name, FireDepot* base) : Vehicle(cur_pos, destination, name) {
	REQUIRE( ( (base != NULL) || (base->isInitialized()) ), "The reference to the base does not exist");

	FireTruck::fMyself = this;
	FireTruck::fBase = base;

	ENSURE(isInitialized(), "The FireTruck is not initialized properly");
}

bool FireTruck::setBase(FireDepot* base) {
	REQUIRE(this->isInitialized(), "The FireTruck object is not initialized properly");
	REQUIRE( ( (base != NULL) || (base->isInitialized()) ), "The reference to the base does not exist");

	FireTruck::fBase = base;

	ENSURE(this->fBase == base, "The base is not set");
	return true;
}

FireDepot* FireTruck::getBase() {
	REQUIRE(this->isInitialized(), "The FireTruck object is not initialized properly");
	return FireTruck::fBase;
}
