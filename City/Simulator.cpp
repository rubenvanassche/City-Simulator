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

	std::vector<Building*> vecBuildings;

	std::vector<FireDepot*> vecFireDepots = fTown->getFireDepots();
	std::vector<Hospital*> vecHospitals = fTown->getHospitals();
	std::vector<House*> vecHouses = fTown->getHouses();
	std::vector<Shop*> vecShops = fTown->getShops();
	std::vector<PoliceDepot*> vecPoliceDepots = fTown->getPoliceDepots();

	for (unsigned int index = 0; index < vecFireDepots.size(); index++) {
		if (vecFireDepots[index]->isBurning()) {
			continue;	// depot is already burning
		}
		else if (vecFireDepots[index]->isDead()) {
			continue;	// depot is burnt down
		}
		else {
			vecBuildings.push_back(vecFireDepots[index]);
		}
	}

	for (unsigned int index = 0; index < vecHospitals.size(); index++) {
		if (vecHospitals[index]->isBurning()) {
			continue;	// depot is already burning
		}
		else if (vecHospitals[index]->isDead()) {
			continue;	// depot is burnt down
		}
		else {
			vecBuildings.push_back(vecHospitals[index]);
		}
	}

	for (unsigned int index = 0; index < vecHouses.size(); index++) {
		if (vecHouses[index]->isBurning()) {
			continue;	// depot is already burning
		}
		else if (vecHouses[index]->isDead()) {
			continue;	// depot is burnt down
		}
		else {
			vecBuildings.push_back(vecHouses[index]);
		}
	}

	for (unsigned int index = 0; index < vecShops.size(); index++) {
		if (vecShops[index]->isBurning()) {
			continue;	// depot is already burning
		}
		else if (vecShops[index]->isDead()) {
			continue;	// depot is burnt down
		}
		else {
			vecBuildings.push_back(vecShops[index]);
		}
	}

	for (unsigned int index = 0; index < vecPoliceDepots.size(); index++) {
		if (vecPoliceDepots[index]->isBurning()) {
			continue;	// depot is already burning
		}
		else if (vecPoliceDepots[index]->isDead()) {
			continue;	// depot is burnt down
		}
		else {
			vecBuildings.push_back(vecPoliceDepots[index]);
		}
	}

	int index = std::rand() % vecBuildings.size();
	vecBuildings[index]->setFire();

	return;
}

void Simulator::fireTruckControl() {
	REQUIRE(this->isInitialized(), "Simulator is initialized");

	std::vector<Building*> vecBuildings;
	std::vector<FireDepot*> vecFireDepotsOnFire;
	std::vector<FireTruck*> vecTrucksArrived;
	std::vector<FireTruck*> vecTrucksInDepot;

	std::vector<FireDepot*> vecFireDepots = fTown->getFireDepots();
	std::vector<Hospital*> vecHospitals = fTown->getHospitals();
	std::vector<House*> vecHouses = fTown->getHouses();
	std::vector<Shop*> vecShops = fTown->getShops();
	std::vector<PoliceDepot*> vecPoliceDepots = fTown->getPoliceDepots();
	std::vector<FireTruck*> vecTrucks = fTown->getFireTrucks();

	for (unsigned int index = 0; index < vecHospitals.size(); index++) {
		if (vecHospitals[index]->isBurning()) {
			vecBuildings.push_back(vecHospitals[index]);
		}
	}

	for (unsigned int index = 0; index < vecHouses.size(); index++) {
		if (vecHouses[index]->isBurning()) {
			vecBuildings.push_back(vecHouses[index]);
		}
	}

	for (unsigned int index = 0; index < vecShops.size(); index++) {
		if (vecShops[index]->isBurning()) {
			vecBuildings.push_back(vecShops[index]);
		}
	}

	for (unsigned int index = 0; index < vecPoliceDepots.size(); index++) {
		if (vecPoliceDepots[index]->isBurning()) {
			vecBuildings.push_back(vecPoliceDepots[index]);
		}
	}

	for (unsigned int index = 0; index < vecFireDepots.size(); index++) {
		if (vecFireDepots[index]->isBurning()) {
			vecFireDepotsOnFire.push_back(vecFireDepots[index]);
		}
	}

	for (unsigned int index = 0; index < vecTrucks.size(); index++) {
		if (vecTrucks[index]->isInDepot()) {
			vecTrucksInDepot.push_back(vecTrucks[index]);
		}
		else if (vecTrucks[index]->isArrived() ) {
			vecTrucksArrived.push_back(vecTrucks[index]);
		}
		else {	// truck is on way
			continue;
		}
	}

	// iterate over buildings that is on fire (except firedepot, that is a special case)
	for (unsigned int index = 0; index < vecBuildings.size(); index++) {
		if (vecBuildings[index]->isFireTruckAssigned() ) {
			continue;	// there is already a firetruck on way
		}

		if (vecTrucksInDepot.empty()) {
			continue;	// you have bad luck, there isn't any available fireTruck that is in the depot
		}

		// otherwise, choose a random truck
		int i = std::rand() % vecTrucksInDepot.size();
		FireTruck* truck = vecTrucksInDepot.at(i);

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
	for (unsigned int index = 0; index < vecFireDepotsOnFire.size(); index++) {
		// if there are trucks in the depot, then stop the fire
		if (vecFireDepotsOnFire[index]->getAvailableVehicles() > 0) {
			vecFireDepotsOnFire[index]->stopFire();
		}
	}

	// finally, check whether there are trucks arrived, so they can extinguish and send back to it's base
	for (unsigned int index = 0; index < vecTrucksArrived.size(); index++) {
		if (vecTrucksArrived[index]->isAtEntranceDepot()) {
			// first check whether it's base is on fire, then enter depot
			if (vecTrucks[index]->getBase()->isBurning()) {
				vecTrucks[index]->getBase()->stopFire();
			}

			vecTrucks[index]->enterDepot();
		}
		else {	// truck is on a building
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

	std::vector<FireDepot*> vecFireDepots = fTown->getFireDepots();
	std::vector<Hospital*> vecHospitals = fTown->getHospitals();
	std::vector<House*> vecHouses = fTown->getHouses();
	std::vector<Shop*> vecShops = fTown->getShops();
	std::vector<PoliceDepot*> vecPoliceDepots = fTown->getPoliceDepots();

	for (unsigned int index = 0; index < vecHospitals.size(); index++) {
		if (vecHospitals[index]->isBurning()) {
			vecHospitals[index]->burningDown();
		}
	}

	for (unsigned int index = 0; index < vecHouses.size(); index++) {
		if (vecHouses[index]->isBurning()) {
			vecHouses[index]->burningDown();
		}
	}

	for (unsigned int index = 0; index < vecShops.size(); index++) {
		if (vecShops[index]->isBurning()) {
			vecShops[index]->burningDown();
		}
	}

	for (unsigned int index = 0; index < vecPoliceDepots.size(); index++) {
		if (vecPoliceDepots[index]->isBurning()) {
			vecPoliceDepots[index]->burningDown();
		}
	}

	for (unsigned int index = 0; index < vecFireDepots.size(); index++) {
		if (vecFireDepots[index]->isBurning()) {
			vecFireDepots[index]->burningDown();
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

	std::vector<Shop*> vecShops = fTown->getShops();
	for (unsigned int index = 0; index < vecShops.size(); index++) {
		if (vecShops[index]->isRobbing()) {
			vecShops[index]->rob(1);
		}
	}

	return;
}

void Simulator::policeTruckControl() {
	REQUIRE(this->isInitialized(), "Simulator is initialized");

	std::vector<Shop*> robbingShops;
	std::vector<PoliceTruck*> trucksInDepot;
	std::vector<PoliceTruck*> trucksArrived;

	std::vector<Shop*> vecShops = fTown->getShops();
	std::vector<PoliceTruck*> vecTrucks = fTown->getPoliceTrucks();

	for (unsigned int index = 0; index < vecShops.size(); index++) {
		if (vecShops[index]->isRobbing()) {
			robbingShops.push_back(vecShops[index]);
		}
	}

	for (unsigned int index = 0; index < vecTrucks.size(); index++) {
		if (vecTrucks[index]->isInDepot()) {
			trucksInDepot.push_back(vecTrucks[index]);
		}
		else if (vecTrucks[index]->isArrived()) {
			trucksArrived.push_back(vecTrucks[index]);
		}
		else {	// truck is on way
			continue;
		}
	}

	for (unsigned int index = 0; index < robbingShops.size(); index++) {
		if (robbingShops[index]->isPoliceTruckAssigned() ) {
			continue;	// there is already a policetruck assigned
		}

		// let's try to assign a policeTruck to the shop being robbed
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
	for (unsigned int index = 0; index < trucksArrived.size(); index++) {
		if (trucksArrived[index]->isAtEntranceDepot()) {
			// first check whether it's base is on fire or not
			if (trucksArrived[index]->getBase()->isBurning()) {
				continue;	// then wait for the firetruck
			}
			else {
				vecTrucks[index]->enterDepot();
			}
		}
		else {	// the police is at a building
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

	std::vector<Vehicle*> vecTrucks;

	std::vector<FireTruck*> vecFireTrucks = fTown->getFireTrucks();
	std::vector<PoliceTruck*> vecPoliceTrucks = fTown->getPoliceTrucks();

	for (unsigned int index = 0; index < vecFireTrucks.size(); index++) {
		if (vecFireTrucks[index]->isOnWay()) {
			vecTrucks.push_back(vecFireTrucks[index]);
		}
	}

	for (unsigned int index = 0; index < vecPoliceTrucks.size(); index++) {
		if (vecPoliceTrucks[index]->isOnWay()) {
			vecTrucks.push_back(vecPoliceTrucks[index]);
		}
	}

	// okay, then iterate over trucks on way and drive them through city
	for (unsigned int index = 0; index < vecTrucks.size(); index++) {
		Point curPos = vecTrucks[index]->getPosition();
		Point destination = vecTrucks[index]->getDestination();

		Point next = fTown->nextStep(curPos, destination);

		if (curPos.getX() == next.getX()) {
			if (next.getY() > curPos.getY()) {
				vecTrucks[index]->goUp();
			}
			else {
				vecTrucks[index]->goDown();
			}
		}
		else if (curPos.getY() == next.getY()) {
			if (next.getX() > curPos.getX()) {
				vecTrucks[index]->goRight();
			}
			else {
				vecTrucks[index]->goLeft();
			}
		}
	}

	return;
}

void Simulator::repairBuildings() {
	REQUIRE(this->isInitialized(), "Simulator is initialized");

	std::vector<Building*> vecBuildings;

	std::vector<FireDepot*> vecFireDepots = fTown->getFireDepots();
	std::vector<Hospital*> vecHospitals = fTown->getHospitals();
	std::vector<House*> vecHouses = fTown->getHouses();
	std::vector<Shop*> vecShops = fTown->getShops();
	std::vector<PoliceDepot*> vecPoliceDepots = fTown->getPoliceDepots();

	for (unsigned int index = 0; index < vecHospitals.size(); index++) {
		if (vecHospitals[index]->startRepair()) {
			vecBuildings.push_back(vecHospitals[index]);
		}
	}

	for (unsigned int index = 0; index < vecHouses.size(); index++) {
		if (vecHouses[index]->startRepair()) {
			vecBuildings.push_back(vecHouses[index]);
		}
	}

	for (unsigned int index = 0; index < vecShops.size(); index++) {
		if (vecShops[index]->startRepair()) {
			vecBuildings.push_back(vecShops[index]);
		}
	}

	for (unsigned int index = 0; index < vecPoliceDepots.size(); index++) {
		if (vecPoliceDepots[index]->startRepair()) {
			vecBuildings.push_back(vecPoliceDepots[index]);
		}
	}

	for (unsigned int index = 0; index < vecFireDepots.size(); index++) {
		if (vecFireDepots[index]->startRepair()) {
			vecBuildings.push_back(vecFireDepots[index]);
		}
	}


	for (unsigned int index = 0; index < vecBuildings.size(); index++) {
		vecBuildings[index]->repair();
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

