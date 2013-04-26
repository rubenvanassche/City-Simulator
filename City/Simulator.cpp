/*
 * Simulator.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	2.0
 * @date:		Friday 26 April 2013
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

	ENSURE(this->isInitialized(), "Simulator is initialized");
	ENSURE(this->fTown == town, "Town is set");
}

bool Simulator::endSimulation() const {
	REQUIRE(this->isInitialized(), "Simulator is initialized");

	return fTown->isDead();
}

void Simulator::fireBreaksOut() {
	REQUIRE(this->isInitialized(), "Simulator is initialized");

	std::vector<Building*> vecBuildings = fTown->getBuildingsNotOnFire();

	int index = std::rand() % vecBuildings.size();
	vecBuildings[index]->setFire();

	return;
}

void Simulator::fireTruckControl() {
	REQUIRE(this->isInitialized(), "Simulator is initialized");

	// iterate over buildings that is on fire (except firedepot, that is a special case)
	std::vector<Building*> vecBuildings = fTown->getBuildingsOnFire();
	for (unsigned int index = 0; index < vecBuildings.size(); index++) {

		if (vecBuildings[index]->isFireTruckAssigned() ) {
			continue;
		}

		// if no firetruck assigned, then try to send a firetruck
		std::vector<FireTruck*> vecTrucks = fTown->getFireTrucksInDepot();
		if (vecTrucks.empty()) {
			continue;	// you have bad luck, there isn't a fireTruck that is in the depot available
		}

		int i = std::rand() % vecTrucks.size();
		FireTruck* truck = vecTrucks.at(i);

		// okay, then find a location where the truck must go
		Point destination = vecBuildings[index]->getLocation();
		int x = destination.getX();
		int y = destination.getY();
		int width = vecBuildings[index]->getSize().getWidth();
		int height = vecBuildings[index]->getSize().getHeight();

		if (!fTown->isInMap(destination)) {
			destination.set(x, y + 1);
		}
		if(!fTown->isInMap(destination)) {
			destination.set(x + width, y);
		}
		if (!fTown->isInMap(destination)) {
			destination.set(x, y - height);
		}
		if (!fTown->isInMap(destination)) {
			destination.set(x - 1, y);
		}

		vecBuildings[index]->assignFireTruck();
		truck->send(vecBuildings[index], destination);
	}

	// then iterate over firedepots on fire
	std::vector<FireDepot*> vecDepots = fTown->getFireDepotsOnFire();
	for (unsigned int index = 0; index < vecDepots.size(); index++) {
		// if there are trucks in the depot, then stop the fire
		if (vecDepots[index]->getAvailableVehicles() > 0) {
			vecDepots[index]->stopFire();
		}
	}

	// finally, check whether there are trucks arrived, so they can extinguish and send back to it's base
	std::vector<FireTruck*> vecTrucks = fTown->getFireTrucksArrived();
	for (unsigned int index = 0; index < vecTrucks.size(); index++) {
		if (vecTrucks[index]->isAtEntranceDepot()) {
			if (vecTrucks[index]->getBase()->isBurning()) {
				vecTrucks[index]->getBase()->stopFire();
			}

			vecTrucks[index]->enterDepot();
		}
		else {
			Building* buildingOnFire = vecTrucks[index]->getBuilding();
			buildingOnFire->stopFire();
			vecTrucks[index]->sendBack();
			buildingOnFire->withdrawFireTruckAssignment();
		}
	}

	return;
}

void Simulator::burningDown() {
	REQUIRE(this->isInitialized(), "Simulator is initialized");

	std::vector<Building*> vecBuildings = fTown->getBuildingsOnFire();
	for (unsigned int index = 0; index < vecBuildings.size(); index++) {
		vecBuildings[index]->burningDown();
	}

	std::vector<FireDepot*> vecDepots = fTown->getFireDepotsOnFire();
	for (unsigned int index = 0; index < vecDepots.size(); index++) {
		if (vecDepots[index]->getAvailableVehicles() > 0) {
			vecDepots[index]->stopFire();
			continue;
		}
		else {
			vecDepots[index]->burningDown();
		}
	}

	return;
}

void Simulator::commitRob() {
	REQUIRE(this->isInitialized(), "Simulator is initialized");

	Shop* ptrShop = fTown->randShop();
	ptrShop->startRobbing();
	return;
}

void Simulator::robbing() {
	REQUIRE(this->isInitialized(), "Simulator is initialized");

	std::vector<Shop*> robbingShops = fTown->getRobbingShops();
	for (unsigned int index = 0; index < robbingShops.size(); index++) {
		robbingShops[index]->rob(1);
	}

	return;
}

void Simulator::policeTruckControl() {
	REQUIRE(this->isInitialized(), "Simulator is initialized");

	std::vector<Shop*> robbingShops = fTown->getRobbingShops();
	for (unsigned int index = 0; index < robbingShops.size(); index++) {
		if (robbingShops[index]->isPoliceTruckAssigned() ) {
			continue;
		}

		// let's try to assign a policeTruck to the shop being robbed
		std::vector<PoliceTruck*> trucksInDepot = fTown->getPoliceTrucksInDepot();
		if (trucksInDepot.empty()) {
			continue;	// bad luck, there are no policetrucks avialable
		}

		int i = std::rand() % trucksInDepot.size();
		PoliceTruck* truck = trucksInDepot.at(i);

		// okay, then find a point where the truck has to drive to
		Point destination = robbingShops[index]->getLocation();
		int x = destination.getX();
		int y = destination.getY();
		int width = robbingShops[index]->getSize().getWidth();
		int height = robbingShops[index]->getSize().getHeight();

		if (!fTown->isInMap(destination)) {
			destination.set(x, y + 1);
		}
		if(!fTown->isInMap(destination)) {
			destination.set(x + width, y);
		}
		if (!fTown->isInMap(destination)) {
			destination.set(x, y - height);
		}
		if (!fTown->isInMap(destination)) {
			destination.set(x - 1, y);
		}

		robbingShops[index]->assignPoliceTruck();
		truck->send(robbingShops[index], destination);
	}


	// also sendback trucks that is arrived
	std::vector<PoliceTruck*> vecTrucks = fTown->getPoliceTrucksArrived();
	for (unsigned int index = 0; index < vecTrucks.size(); index++) {
		if (vecTrucks[index]->isAtEntranceDepot()) {
			vecTrucks[index]->enterDepot();
		}
		else {
			Shop* robbedShop = vecTrucks[index]->getShop();
			robbedShop->stopRobbing();
			vecTrucks[index]->sendBack();
			robbedShop->withdrawPoliceTruckAssignment();
		}
	}

	return;
}

void Simulator::repairBuildings() {
	std::vector<Building*> vecBuilding = fTown->getBuildingsToRepair();

	for (unsigned int index = 0; index < vecBuilding.size(); index++) {
		vecBuilding[index]->repair();
	}
	return;
}

/*
void spreadFire(){
	// todo: this
	// iterate over each house that is burning and check if spreadfire() is true
	// if so use the calculateSurroundingPoints() function
	// then make a vector with all the points of houses by using calculatepoints() (this must be done only once)
	// then check if there are equivalent points between those two vetcors and put these points in yet another vector!
	// Then select a random house from this vector and set it on fire

	// Do the same with shops
	// use the pregenerated points of houses vector generated some lines above
	// check again for equivalent points and set 2 houses on fire
}
*/
/*
void Simulator::step(){
	// todo: almost done
	this->fireBreaksOut();
	this->burningDown();
	this->robbing();
	this->drive();
	this->fireTruckControl();
	this->policeTruckControl();
	this->spreadFire();
}
*/
