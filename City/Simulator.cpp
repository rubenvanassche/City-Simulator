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

void Simulator::drive() {
	REQUIRE(this->isInitialized(), "Simulator is initialized");

	std::vector<FireTruck*> vecFTrucks = fTown->getFireTrucksOnWay();
	std::vector<PoliceTruck*> vecPTrucks = fTown->getPoliceTrucksOnWay();

	for (unsigned int index = 0; index < vecFTrucks.size(); index++) {
		Point curPos = vecFTrucks[index]->getPosition();
		Point destination = vecFTrucks[index]->getDestination();

		Point next = fTown->nextStep(curPos, destination);

		if (curPos.getX() == next.getX()) {
			if (next.getY() > curPos.getY()) {
				vecFTrucks[index]->goUp();
			}
			else {
				vecFTrucks[index]->goDown();
			}
		}
		else if (curPos.getY() == next.getY()) {
			if (next.getX() > curPos.getX()) {
				vecFTrucks[index]->goRight();
			}
			else {
				vecFTrucks[index]->goLeft();
			}
		}
	}

	for (unsigned int index = 0; index < vecPTrucks.size(); index++) {
		Point curPos = vecPTrucks[index]->getPosition();
		Point destination = vecPTrucks[index]->getDestination();

		Point next = fTown->nextStep(curPos, destination);

		if (curPos.getX() == next.getX()) {
			if (next.getY() > curPos.getY()) {
				vecPTrucks[index]->goUp();
			}
			else {
				vecPTrucks[index]->goDown();
			}
		}
		else if (curPos.getY() == next.getY()) {
			if (next.getX() > curPos.getX()) {
				vecPTrucks[index]->goRight();
			}
			else {
				vecPTrucks[index]->goLeft();
			}
		}
	}
}

void Simulator::repairBuildings() {
	REQUIRE(this->isInitialized(), "Simulator is initialized");

	std::vector<Building*> vecBuilding = fTown->getBuildingsToRepair();

	for (unsigned int index = 0; index < vecBuilding.size(); index++) {
		vecBuilding[index]->repair();
	}
	return;
}


void Simulator::spreadFire(){
	typedef std::pair<Point,House*> HousePoint;

	std::vector<HousePoint> allHouses; // All Points in the map + their houses

	std::vector<House*> houses = fTown->getHouses();

	for(unsigned int i = 0;i < houses.size();i++){
		std::vector<Point> housePoints = (*houses.at(i)).calculatePoints();
		for(unsigned int j = 0;j < housePoints.size();j++){
			HousePoint newHousePoint;
			newHousePoint.first = housePoints.at(j);
			newHousePoint.second = houses.at(i);

			allHouses.push_back(newHousePoint);
		}
	}

	for(unsigned int i = 0;i < houses.size();i++){
		if((*houses.at(i)).startSpreadingFire()){
			// Jeej, we can set other buildings on fire!

			std::vector<HousePoint> nextTargets; // Houses surrounding this house we can set on fire
			std::vector<Point> surroundingPoints = (*houses.at(i)).calculateSurroundingPoints(); // All the points surroundig the house that will spread fire

			for(unsigned int j = 0;j < surroundingPoints.size();j++){
				for(unsigned int k = 0;k < allHouses.size();k++){
					// now check with the points in the allHouses vector if one has a point equal to the current surrounding point wer're investigating then add it to the nextTargets vector
					if( allHouses.at(k).first == surroundingPoints.at(j) ){
						HousePoint nextTarget;
						nextTarget.first = surroundingPoints.at(j);
						nextTarget.second = allHouses.at(k).second;

						nextTargets.push_back(nextTarget);
					}
				}
			}

			// Now we need to select a random house in the nextTargets vector and set it on fire
			if(nextTargets.size() >= 1){
				int randomIndex = rand() % nextTargets.size();
				(*nextTargets.at(randomIndex).second).setFire();
			}
		}
	}

	// Now do the same thing with shops

	std::vector<Shop*> shops = fTown->getShops();

	for(unsigned int i = 0;i < shops.size();i++){
		if((*shops.at(i)).startSpreadingFire()){
			// Jeej, we can set other buildings on fire!

			std::vector<HousePoint> nextTargets; // Houses surrounding this house we can set on fire
			std::vector<Point> surroundingPoints = (*shops.at(i)).calculateSurroundingPoints(); // All the points surroundig the house that will spread fire

			for(unsigned int j = 0;j < surroundingPoints.size();j++){
				for(unsigned int k = 0;k < allHouses.size();k++){
					// now check with the points in the allHouses vector if one has a point equal to the current surrounding point wer're investigating then add it to the nextTargets vector
					if( allHouses.at(k).first == surroundingPoints.at(j) ){
						HousePoint nextTarget;
						nextTarget.first = surroundingPoints.at(j);
						nextTarget.second = allHouses.at(k).second;

						nextTargets.push_back(nextTarget);
					}
				}
			}

			// Now we need to select a random house in the nextTargets vector and set it on fire
			if(nextTargets.size() >= 2){
				int randomIndex = rand() % nextTargets.size();
				(*nextTargets.at(randomIndex).second).setFire();
				int randomIndex2 = rand() % nextTargets.size();
				(*nextTargets.at(randomIndex2).second).setFire();
			}else if(nextTargets.size() == 1){
				int randomIndex = rand() % nextTargets.size();
				(*nextTargets.at(randomIndex).second).setFire();
			}
		}
	}
}


void Simulator::step(){
	this->fireBreaksOut();
	this->burningDown();
	this->robbing();
	this->drive();
	this->fireTruckControl();
	this->policeTruckControl();
	this->spreadFire();
}

