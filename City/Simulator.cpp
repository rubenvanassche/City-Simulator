/*
 * Simulator.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		Saturday 16 March 2013
 * 
 */

#include "Simulator.h"
#include <cstdlib>

bool Simulator::isInitialized() const {
	return this == Simulator::fMyself;
}

Simulator::Simulator(City* town) {
	REQUIRE(town->isInitialized(), "City is initialized");

	fMyself = this;
	fTown = town;
	fEndSimulation = false;

	ENSURE(this->isInitialized(), "Simulator is initialized");
	ENSURE(this->fTown == town, "city is set");
}

bool Simulator::endSimulation() const {
	REQUIRE(this->isInitialized(), "Simulator is initialized");

	return fEndSimulation;
}

void Simulator::fireBreaksOut() {
	REQUIRE(this->isInitialized(), "Simulator is initialized");

	// to do:
	// select first a random type of building
	// then select in the vector of that building type a single building
	// if the type of building is a firedepot, then check if there are firetrucks avaible in this depot and if so stop the fire, DO NOT SET THE FIRETRUCKSSIGNED BOOL TO TRUE
	// if an other type, set that thing on fire

	//ptrBuild->setFire();
	return;
}

void fireTruckControl(){
	// to do:
	// check vector with burning buildings
	// check for each building if the firetruckassigned bool is true/false
	// if true go to the next building in the vector
	// if false check if there is a fire truck avaible and send that one and don't forget to update the firetruck assigned bool

	// + check if a firetruck is at his destination
	// if so stop fire and send back to the firedepot
	// if not  continue driving(so nothing todo here)
}

void Simulator::burningDown() {

	// to do:
	// everything!
	// for all buildings except for a fireDepot, check if the FireTruckAssigned bool is true if so : just use the burningdown() function
	// if not : check if there is a firetrcuk avaible and send it + set the FireTruckAssigned bool to true

	/*
	std::vector< std::pair<Building*, EBuilding> > vecBuilding = fTown->getBuildingsOnFire();

	for (unsigned int index = 0; index < vecBuilding.size(); index++) {
		if (vecBuilding[index].second == kHOUSE) {
			vecBuilding[index].first->burningDown(); // substract 1
		}
		else if (vecBuilding[index].second == kFIREDEPOT) {
			vecBuilding[index].first->burningDown();
		}
		else if (vecBuilding[index].second == kSHOP) {
			vecBuilding[index].first->burningDown();
		}
		else {
			// you've forgotten the case of hospitals/policedepot in Spec2.0
			vecBuilding[index].first->burningDown();	// let's explode them out of city :--p
		}
	}
	*/

	return;
}

void Simulator::commitRob() {
	Shop* ptrShop = fTown->randShop();
	ptrShop->StartRobbing();

	return;
}

void Simulator::robbing() {
	std::vector<Shop*> robbedShops = fTown->getRobbingShop();

	for (unsigned int index = 0; index < robbedShops.size(); index++) {
		robbedShops[index]->rob();
	}
	return;
}

void policeTruckControl(){
	// check the vector of shops being robbed
	// check for each shop if there is a Police Car assigned
	// if not check if there are avaible and send one
	// if assigned, go to the next shop

	// + check if a polcietruck is at his destination
	// if so stop robbing and send back to the policeDepot
	// if not continue driving(so nothing todo here)
}

void repairBuildings(){
	// iterate over each building(so over each building type vector)
	// and use the repair() function
}

void spreadFire(){
	// iterate over each house that is burning and check if spreadfire() is true
	// if so use the calculateSurroundingPoints() function
	// then make a vector with all the points of houses by using calculatepoints() (this must be done only once)
	// then check if there are equivalent points between those two vetcors and put these points in yet another vector!
	// Then select a random house from this vector and set it on fire

	// Do the same with shops
	// use the pregenerated points of houses vector generated some lines above
	// check again for equivalent points and set 2 houses on fire
}

void Simulator::step(){
	this->burningDown();
	this->robbing();
	this->drive();
	this->fireTruckControl();
	this->policeTruckControl();
	this->spreadFire();
}


/*

bool Simulator::drive(int repeat) {
	REQUIRE(this->isInitialized(), "Simulator is initialized");
	REQUIRE(repeat > 0, "repeat at least 1");

	for (int i=0; i < repeat; i++) {
		std::vector<FireTruck*> vehicles = Simulator::fTown->getTrucks();

		for (unsigned int index=0; index < vehicles.size(); index++) {
			if (vehicles[index]->isArrived() ) {
				if (vehicles[index]->isAtEntranceDepot() ) {
					vehicles[index]->enterDepot();	// trucks arrived at the depot
				}
				continue;	// ignore arrived trucks
			}

			Point destination = vehicles[index]->getDestination();
			Point curPos = vehicles[index]->getPosition();

			// first, find the destination street

			Street* destStr;
			destStr = Simulator::fTown->findHorizontalStreet(curPos);
			if (destStr == NULL) {
				destStr = Simulator::fTown->findVerticalStreet(curPos);
			}

			// if we are on the right street already
			if (destStr->isElement(curPos)) {
				if (destStr->isHorizontal() ) {
					if (curPos.getX() < destination.getX() ) {
						vehicles[index]->goRight();
					}
					vehicles[index]->goLeft();
				}
				else {
					if (curPos.getY() < destination.getY() ) {
						vehicles[index]->goUp();
					}
					vehicles[index]->goDown();
				}
			}

			// else, we have to find out on which street we are now
			Street* curStr;
			if (destStr->isHorizontal() ) {	// first search for a crossing street
				curStr = Simulator::fTown->findVerticalStreet(curPos);
				if (curStr == NULL) {
					curStr = Simulator::fTown->findHorizontalStreet(curPos);
				}
			}
			else {
				curStr = Simulator::fTown->findHorizontalStreet(curPos);
				if (curStr == NULL) {
					curStr = Simulator::fTown->findVerticalStreet(curPos);
				}
			}

			Point* cross = Simulator::fTown->findCrosspoint(*destStr, *curStr, curPos);
			if (isParallel(*curStr, *destStr) ) {
				if (curStr->isVertical() ) {
					if (curPos.getY() < cross->getY() ) {
						vehicles[index]->goUp();
						continue;
					}
					vehicles[index]->goDown();
					continue;
				}
				else {	// cur str is horizontal
					if (curPos.getX() < cross->getX() ) {
						vehicles[index]->goRight();
						continue;
					}
					vehicles[index]->goLeft();
					continue;
				}
			}

			if (isCrossing(*curStr, *destStr) ) {
				if (curStr->isVertical() ) {
					if (curPos.getY() < cross->getY() ) {
						vehicles[index]->goUp();
						continue;
					}
					vehicles[index]->goDown();
					continue;
				}
				else {	// cur str is horizontal
					if (curPos.getX() < cross->getX() ) {
						vehicles[index]->goRight();
						continue;
					}
					vehicles[index]->goLeft();
					continue;
				}
			}
		}
	}

	return true;
}

bool Simulator::extinguish() {
	REQUIRE(this->isInitialized(), "Simulator is initialized");

	std::vector<FireTruck*> trucks = Simulator::fTown->getTrucks();
	for (unsigned int index=0; index < trucks.size(); index++) {
		if ( ( trucks[index]->isArrived() ) &&
				( (!trucks[index]->isAtEntranceDepot() ) || (!trucks[index]->isInDepot() ) ) ) {

			trucks[index]->getBuilding()->stopFire();	// stop the fire
			trucks[index]->sendBack();	// send the truck back to the depot
		}
	}
	return true;
}

bool Simulator::sendTrucks() {
	REQUIRE(this->isInitialized(), "Simulator is initialized");

	std::vector<House*> houses = Simulator::fTown->getHouses();
	std::vector<FireTruck*> trucks = Simulator::fTown->getTrucks();

	for (unsigned int index=0; index < houses.size(); index++) {
		if (!houses[index]->isBurning() ) {
			continue;	// ignore house that is not burning
		}

		Point pos = houses[index]->getLocation();
		int originX = pos.getX();
		int originY = pos.getY();

		if ( !Simulator::fTown->isInMap(pos) ) {
			int y = pos.getY() + 1;
			pos.set(originX, y);
		}
		if ( !Simulator::fTown->isInMap(pos) ) {
			int x = pos.getX() - 1;
			pos.set(x, originY);
		}
		if ( !Simulator::fTown->isInMap(pos) ) {
			int x =  originX + houses[index]->getSize().getWidth();
			pos.set(x, originY);
		}
		if ( !Simulator::fTown->isInMap(pos) ) {
			int y = originY - houses[index]->getSize().getHeight();
			pos.set(originX, y);
		}

		for (unsigned int i=0; i < trucks.size(); i++) {
			if (trucks[i]->getBuilding()->getLocation() == houses[index]->getLocation() ) {
				continue;	// ignore this house, a truck is on way
			}

			// else we will send a truck
			if (trucks[i]->isInDepot() ) {
				trucks[i]->send(houses[index], pos);
			}
		}
	}

	return true;
}
*/
