/*
 * House.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Thursday 28 February 2013
 * 
*/

#include "House.h"
#include "DesignByContract.h"

std::ostream& operator<< (std::ostream& stream, House& house){
	Size size = *house.getSize();
	for(int i = 0; i < *size.getHeight(); i++){
		for(int j = 0; j < *size.getWidth(); j++){
			stream << "H";
		}
		stream << std::endl;
	}
	stream << "Health : " << house.fHealth << std::endl;
	return stream;
}

bool House::isInitialized(){
	return this == House::fMyself;
}

House::House(Point& location, int health) : Building(location){
	REQUIRE(location.isInitialized(), "The location is not initialized properly");
	REQUIRE(health >= 0, "The health point is not >= 0");

	Size size(2);

	this->setSize(size);
	House::fHealth = health;
	House::fIsBurning = false;
	House::fMyself = this;

	ENSURE(isInitialized(), "The House object is not initialized properly");
}

House::House(House& h) : Building(*h.getLocation()) {
	Size size(2);
	this->setSize(size);

	House::fHealth = h.fHealth;
	House::fIsBurning = h.fIsBurning;
	House::fMyself = this;
}

House& House::operator= (House& h) {
	this->setSize(*h.getSize());
	this->setLocation(*h.getLocation());

	House::fHealth = h.fHealth;
	House::fIsBurning = h.fIsBurning;
	return *this;
}

bool House::isBurning(){
	REQUIRE(this->isInitialized(), "The House object is not initialized properly");

	return House::fIsBurning;
}


bool House::setFire(){
	REQUIRE(this->isInitialized(), "The House object is not initialized properly");

	House::fIsBurning = true;

	ENSURE(this->fIsBurning == true, "The house is not set on fire");
	return true;
}


bool House::stopFire(){
	REQUIRE(this->isInitialized(), "The House object is not initialized properly");

	House::fIsBurning = false;

	ENSURE(this->fIsBurning == false, "The fire on the house is not stopped");
	return true;
}


bool House::setHealth(int health){
	REQUIRE(this->isInitialized(), "The House object is not initialized properly");
	REQUIRE(health >= 0, "The health point is not >= 0");

	House::fHealth = health;

	ENSURE(this->fHealth == health, "The health point is not set");
	return true;
}


 int* House::getHealth(){
	REQUIRE(this->isInitialized(), "The House object is not set properly");
	return &(House::fHealth);
}

bool House::check(int subtracter = 1){
	REQUIRE(this->isInitialized(), "The House object is not initialized properly");
	REQUIRE(subtracter >= 0, "The subtracter is  not >= 0");
	REQUIRE(subtracter > *(this->getHealth()), "The subtracter is greater then the health");

	if(fIsBurning == true){
		this->setHealth(fHealth - subtracter);
	}
	return true;
}


