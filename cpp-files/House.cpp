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
	Size size = objectDepot.getSize();
	for(int i = 0; i < size.getHeight; i++){
		for(int j = 0; j < size.getWidth; j++){
			stream << "H";
		}
		stream << std::endl;
	}
	stream << "Health : " << fHealth << std::endl;
	return stream;
}

bool isInitialized(){
	return this == House::fMyself;
}

House(const Point& location,  int health){
	REQUIRE(location.isInitialized(), "The location is not initialized properly");
	REQUIRE(health >= 0, "The health point is not >= 0");

	fLocation = location;
	fHealth = health;
	fIsBurning = false;

	ENSURE(isInitialized(), "The House object is not initialized properly");
}


bool isBurning(){
	REQUIRE(this->isInitialized(), "The House object is not initialized properly");

	return fIsBurning;
}


bool setFire(){
	REQUIRE(this->isInitialized(), "The House object is not initialized properly");

	fIsBurning = true;

	ENSURE(this->fIsBurning == true, "The house is not set on fire");
}


bool stopFire(){
	REQUIRE(this->isInitialized(), "The House object is not initialized properly");

	fIsBurning = false;

	ENSURE(this->fIsBurning == false, "The fire on the house is not stopped");
}


bool setHealth(const  int& health){
	REQUIRE(this->isInitialized(), "The House object is not initialized properly");
	REQUIRE(health >= 0, "The health point is not >= 0");

	fHealth = health;

	ENSURE(this->fHealth == health, "The health point is not set");
}


 int getHealth(){
	REQUIRE(this->isInitialized(), "The House object is not set properly");
	ENSURE(this->fHealth >= 0, "The returned health point is not valid");

	return fHealth;
}

bool check(const int& subtracter = 1){
	REQUIRE(this->isInitialized(), "The House object is not initialized properly");
	REQUIRE(subtracter >= 0, "The subtracter is  not >= 0");
	REQUIRE(subtracter > this->getHealth(), "The subtracter is greater then the health");

	if(fIsBurning == true){
		this->setHealth(fHealth - subtracter);
	}
}


