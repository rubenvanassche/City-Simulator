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

	int type = std::rand() % 5;
	if (type == 0) {
		FireDepot* depot = fTown->randFireDepot();
		depot->setFire();
		return;
	}
	else if (type == 1) {
		PoliceDepot* depot = fTown->randPoliceDepot();
		depot->setFire();
		return;
	}
	else if (type == 2) {
		Hospital* hosp = fTown->randHospital();
		hosp->setFire();
		return;
	}
	else if (type == 3) {
		Shop* shop = fTown->randShop(true, false);
		shop->setFire();
		return;
	}
	else if (type == 4) {
		House* h = fTown->randHouse();
		h->setFire();
		return;
	}

	return;
}

void Simulator::fireTruckControl() {
	REQUIRE(this->isInitialized(), "Simulator is initialized");

	std::vector<FireTruck*> vecTrucks = fTown->getFireTrucksArrived();
	for (unsigned int index = 0; index < vecTrucks.size(); index++) {
		if (vecTrucks[index]->isAtEntranceDepot()) {
			vecTrucks[index]->enterDepot();
		}
		else {
			Building* buildingOnFire = vecTrucks[index]->getBuilding();
			buildingOnFire->stopFire();
			vecTrucks[index]->sendBack();
		}
	}

	return;
}
/*
void Simulator::burningDown() {

	// todo:
	// everything!
	// for all buildings except for a fireDepot, check if the FireTruckAssigned bool is true if so : just use the burningdown() function
	// if not : check if there is a firetrcuk avaible and send it + set the FireTruckAssigned bool to true

	std::vector<Building*> vecBuildings = fTown->getBuildingsOnFire();

	for (unsigned int index = 0; index < vecBuildings.size(); index++) {
		if (vecBuildings[index]->isFireTruckAssigned()) {
			continue;
		}

		std::vector<>
		FireTruck* truck = fTown->getFireTrucksInDepot().front();

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


}

/*
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
	// todo: here
	// check the vector of shops being robbed
	// check for each shop if there is a Police Car assigned
	// if not check if there are avaible and send one
	// if assigned, go to the next shop

	// + check if a polcietruck is at his destination
	// if so stop robbing and send back to the policeDepot
	// if not continue driving(so nothing to do here)
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
*/

/*
void Simulator::step(){
	this->burningDown();
	this->robbing();
	this->drive();
	this->fireTruckControl();
	this->policeTruckControl();
	this->spreadFire();
}
*/
