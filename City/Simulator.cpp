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

Simulator::Simulator(City* town, Output* output) {
	REQUIRE(town->isInitialized(), "City is initialized");
	REQUIRE(output->isInitialized(), "Output is initialized");

	fMyself = this;
	fTown = town;
	fOutput = output;

	ENSURE(this->isInitialized(), "Simulator is initialized");
	ENSURE(this->fTown == town, "Town is set");
	ENSURE(this->fOutput == output, "output is set");
}

bool Simulator::endSimulation() const {
	REQUIRE(this->isInitialized(), "Simulator is initialized");

	return fTown->isDead();
}

bool Simulator::fireBreaksOut() {
	REQUIRE(this->isInitialized(), "Simulator is initialized");
	//REQUIRE(this->endSimulation() == false, "Not the end of simulation");

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
		else if (vecShops[index]->isRobbing()) {
			continue;	// there's already a crime going on
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

	if (vecBuildings.empty()) {
		return false;	// there isn't one building that is not on fire or not burnt down
	}

	int index = std::rand() % vecBuildings.size();
	vecBuildings[index]->setFire();

	return true;
}

bool Simulator::sendFireTrucks() {
	REQUIRE(this->isInitialized(), "Simulator is initialized");
	REQUIRE(this->endSimulation() == false, "Not the end of simulation");

	std::vector<FireTruck*> vecAvailableTrucks;

	std::vector<FireTruck*> vecTrucks = fTown->getFireTrucks();
	for (unsigned int index = 0; index < vecTrucks.size(); index++) {
		if (vecTrucks[index]->getBase()->isDead()) {
			continue;
		}
		if (vecTrucks[index]->isInDepot()) {
			vecAvailableTrucks.push_back(vecTrucks[index]);
		}
		else {	// truck is not in depot
			continue;
		}
	}

	if (vecAvailableTrucks.empty()) {
		return false;	// there isn't a firetruck available
	}

	std::vector<Building*> vecBuildingsOnFire;
	std::vector<FireDepot*> vecFireDepotsOnFire;

	std::vector<FireDepot*> vecFireDepots = fTown->getFireDepots();
	std::vector<Hospital*> vecHospitals = fTown->getHospitals();
	std::vector<House*> vecHouses = fTown->getHouses();
	std::vector<Shop*> vecShops = fTown->getShops();
	std::vector<PoliceDepot*> vecPoliceDepots = fTown->getPoliceDepots();

	for (unsigned int index = 0; index < vecHospitals.size(); index++) {
		if (vecHospitals[index]->isBurning()) {
			vecBuildingsOnFire.push_back(vecHospitals[index]);
		}
	}

	for (unsigned int index = 0; index < vecHouses.size(); index++) {
		if (vecHouses[index]->isBurning()) {
			vecBuildingsOnFire.push_back(vecHouses[index]);
		}
	}

	for (unsigned int index = 0; index < vecShops.size(); index++) {
		if (vecShops[index]->isBurning()) {
			vecBuildingsOnFire.push_back(vecShops[index]);
		}
	}

	for (unsigned int index = 0; index < vecPoliceDepots.size(); index++) {
		if (vecPoliceDepots[index]->isBurning()) {
			vecBuildingsOnFire.push_back(vecPoliceDepots[index]);
		}
	}

	for (unsigned int index = 0; index < vecFireDepots.size(); index++) {
		if (vecFireDepots[index]->isBurning()) {
			vecFireDepotsOnFire.push_back(vecFireDepots[index]);
		}
	}

	// then iterate over firedepots on fire
	for (unsigned int index = 0; index < vecFireDepotsOnFire.size(); index++) {
		// if there are trucks in the depot, then stop the fire
		if (vecFireDepotsOnFire[index]->getAvailableVehicles() > 0) {
			vecFireDepotsOnFire[index]->stopFire();
		}
	}

	// iterate over buildings that is on fire (except firedepot, that is a special case)
	for (unsigned int index = 0; index < vecBuildingsOnFire.size(); index++) {
		if (vecBuildingsOnFire[index]->isFireTruckAssigned() ) {
			continue;	// there is already a firetruck on way
		}

		if (vecAvailableTrucks.empty()) {
			continue;	// you have bad luck, there isn't any available fireTruck that is in the depot
		}

		// otherwise, choose a random truck
		int i = std::rand() % vecAvailableTrucks.size();
		FireTruck* truck = vecAvailableTrucks.at(i);
		vecAvailableTrucks.erase(vecAvailableTrucks.begin() + i);

		// okay, then find a location where the truck must go
		Point destination = vecBuildingsOnFire[index]->getLocation();
		int x = destination.getX();
		int y = destination.getY();
		int width = vecBuildingsOnFire[index]->getSize().getWidth();
		int height = vecBuildingsOnFire[index]->getSize().getHeight();

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

		vecBuildingsOnFire[index]->assignFireTruck();
		truck->send(vecBuildingsOnFire[index], destination);
	}

	return true;
}

bool Simulator::burningDown() {
	REQUIRE(this->isInitialized(), "Simulator is initialized");
	REQUIRE(this->endSimulation() == false, "Not the end of simulation");

	std::vector<Building*> vecBuildingsOnFire;
	std::vector<FireDepot*> vecFireDepotsOnFire;

	std::vector<FireDepot*> vecFireDepots = fTown->getFireDepots();
	std::vector<Hospital*> vecHospitals = fTown->getHospitals();
	std::vector<House*> vecHouses = fTown->getHouses();
	std::vector<Shop*> vecShops = fTown->getShops();
	std::vector<PoliceDepot*> vecPoliceDepots = fTown->getPoliceDepots();

	for (unsigned int index = 0; index < vecHospitals.size(); index++) {
		if (vecHospitals[index]->isBurning()) {
			vecBuildingsOnFire.push_back(vecHospitals[index]);
		}
	}

	for (unsigned int index = 0; index < vecHouses.size(); index++) {
		if (vecHouses[index]->isBurning()) {
			vecBuildingsOnFire.push_back(vecHouses[index]);
		}
	}

	for (unsigned int index = 0; index < vecShops.size(); index++) {
		if (vecShops[index]->isBurning()) {
			vecBuildingsOnFire.push_back(vecShops[index]);
		}
	}

	for (unsigned int index = 0; index < vecPoliceDepots.size(); index++) {
		if (vecPoliceDepots[index]->isBurning()) {
			vecBuildingsOnFire.push_back(vecPoliceDepots[index]);
		}
	}

	for (unsigned int index = 0; index < vecFireDepots.size(); index++) {
		if (vecFireDepots[index]->isBurning()) {
			vecFireDepotsOnFire.push_back(vecFireDepots[index]);
		}
	}

	if ( (vecBuildingsOnFire.empty()) && (vecFireDepotsOnFire.empty()) ) {
		return false;	// there are no buildings on fire
	}

	for (unsigned int index = 0; index < vecBuildingsOnFire.size(); index++) {
		vecBuildingsOnFire[index]->burningDown();
	}

	for (unsigned int index = 0;  index < vecFireDepotsOnFire.size(); index++) {
		if (vecFireDepotsOnFire[index]->getAvailableVehicles() > 0) {
			vecFireDepotsOnFire[index]->stopFire();
		}
		else {
			vecFireDepotsOnFire[index]->burningDown();
		}
	}

	return true;
}

bool Simulator::commitRob() {
	REQUIRE(this->isInitialized(), "Simulator is initialized");
	REQUIRE(this->endSimulation() == false, "Not the end of simulation");

	std::vector<Shop*> shopsToBeRobbed;

	std::vector<Shop*> vecShops = fTown->getShops();
	for (unsigned int index = 0; index < vecShops.size(); index++) {
		if (vecShops[index]->isBurning()) {
			continue;	// shop is burning;
		}
		else if (vecShops[index]->isRobbing()) {
			continue;	// shop is already being robbed
		}
		else if (vecShops[index]->isDead()) {
			continue;	// shop is burnt down, no stuffs to steal anymore
		}
		else if (vecShops[index]->isEmpty()) {
			continue;	// shop is empty, so nothing to steal
		}

		shopsToBeRobbed.push_back(vecShops[index]);
	}

	if (shopsToBeRobbed.empty()) {
		return false;	// there is no robbing possible
	}

	int index = std::rand() % shopsToBeRobbed.size();
	shopsToBeRobbed[index]->startRobbing();
	return true;
}

bool Simulator::robbing() {
	REQUIRE(this->isInitialized(), "Simulator is initialized");
	REQUIRE(this->endSimulation() == false, "Not the end of simulation");

	std::vector<Shop*> robbingShops;

	std::vector<Shop*> vecShops = fTown->getShops();
	for (unsigned int index = 0; index < vecShops.size(); index++) {
		if (vecShops[index]->isRobbing()) {
			robbingShops.push_back(vecShops[index]);
		}
	}

	if (robbingShops.empty()) {
		return false;	// no robbing possible
	}

	for (unsigned int index = 0; index < robbingShops.size(); index++) {
		robbingShops[index]->rob();
	}

	return true;
}

bool Simulator::sendPoliceTrucks() {
	REQUIRE(this->isInitialized(), "Simulator is initialized");
	REQUIRE(this->endSimulation() == false, "Not the end of simulation");

	std::vector<PoliceTruck*> vecAvailableTrucks;

	std::vector<PoliceTruck*> vecTrucks = fTown->getPoliceTrucks();
	for (unsigned int index = 0; index < vecTrucks.size(); index++) {
		if (vecTrucks[index]->getBase()->isDead()) {
			continue;
		}
		if (vecTrucks[index]->isInDepot()) {
			vecAvailableTrucks.push_back(vecTrucks[index]);
		}
		else {	// truck is not in depot
			continue;
		}
	}

	if (vecAvailableTrucks.empty()) {
		return false;	// there isn't any policetruck available
	}

	std::vector<Shop*> robbingShops;

	std::vector<Shop*> vecShops = fTown->getShops();
	for (unsigned int index = 0; index < vecShops.size(); index++) {
		if (vecShops[index]->isRobbing()) {
			robbingShops.push_back(vecShops[index]);
		}
	}

	// then iterate over shops that is being robbed
	for (unsigned int index = 0; index < robbingShops.size(); index++) {
		if (robbingShops[index]->isPoliceTruckAssigned() ) {
			continue;	// there is already a policetruck assigned
		}

		// let's try to assign a policeTruck to the shop being robbed
		if (vecAvailableTrucks.empty()) {
			continue;	// bad luck, there are no policetrucks avialable
		}

		int i = std::rand() % vecAvailableTrucks.size();
		PoliceTruck* truck = vecAvailableTrucks.at(i);
		vecAvailableTrucks.erase(vecAvailableTrucks.begin() + i);

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

	return true;
}

bool Simulator::drive() {
	REQUIRE(this->isInitialized(), "Simulator is initialized");
	REQUIRE(this->endSimulation() == false, "Not the end of simulation");

	std::vector<Vehicle*> vecTrucksOnWay;
	std::vector<FireTruck*> vecFireTrucksArrived;
	std::vector<PoliceTruck*> vecPoliceTrucksArrived;

	std::vector<FireTruck*> vecFireTrucks = fTown->getFireTrucks();
	std::vector<PoliceTruck*> vecPoliceTrucks = fTown->getPoliceTrucks();

	for (unsigned int index = 0; index < vecFireTrucks.size(); index++) {
		if (vecFireTrucks[index]->isOnWay()) {
			vecTrucksOnWay.push_back(vecFireTrucks[index]);
		}
		else if (vecFireTrucks[index]->isArrived()) {
			if (!vecFireTrucks[index]->isInDepot()) {
				vecFireTrucksArrived.push_back(vecFireTrucks[index]);
			}
		}
		else {
			continue;
		}
	}

	for (unsigned int index = 0; index < vecPoliceTrucks.size(); index++) {
		if (vecPoliceTrucks[index]->isOnWay()) {
			vecTrucksOnWay.push_back(vecPoliceTrucks[index]);
		}
		else if (vecPoliceTrucks[index]->isArrived()) {
			if (!vecPoliceTrucks[index]->isInDepot()) {
				vecPoliceTrucksArrived.push_back(vecPoliceTrucks[index]);
			}
		}
		else {
			continue;
		}
	}

	if ( (vecTrucksOnWay.empty()) && (vecFireTrucksArrived.empty()) && (vecPoliceTrucksArrived.empty()) ) {
		return false;	// there is no trucks on way or arrived
	}

	// okay, then iterate over trucks on way and drive them through city
	for (unsigned int index = 0; index < vecTrucksOnWay.size(); index++) {
		Point curPos = vecTrucksOnWay[index]->getPosition();
		Point destination = vecTrucksOnWay[index]->getDestination();

		Point next = fTown->nextStep(curPos, destination);

		if (curPos.getX() == next.getX()) {
			if (next.getY() > curPos.getY()) {
				vecTrucksOnWay[index]->goUp();
			}
			else if (next.getY() < curPos.getY()) {
				vecTrucksOnWay[index]->goDown();
			}
			else {
				continue;
			}
		}
		else if (curPos.getY() == next.getY()) {
			if (next.getX() > curPos.getX()) {
				vecTrucksOnWay[index]->goRight();
			}
			else if (next.getX() < curPos.getX()) {
				vecTrucksOnWay[index]->goLeft();
			}
			else {
				continue;
			}
		}
	}

	// then iterate over firetrucks that is arrived
	for (unsigned int index = 0; index < vecFireTrucksArrived.size(); index++) {
		if (vecFireTrucksArrived[index]->isAtEntranceDepot()) {
			// if the depot is burnt down, then continue
			if (vecFireTrucks[index]->getBase()->isDead()) {
				continue;	// trucks will stay at the entrance
			}

			// then check whether it's base is on fire (extinguish if so), then enter depot
			if (vecFireTrucksArrived[index]->getBase()->isBurning()) {
				vecFireTrucksArrived[index]->getBase()->stopFire();
			}

			vecFireTrucksArrived[index]->enterDepot();
		}
		else {	// truck is on a building
			Building* buildingOnFire = vecFireTrucksArrived[index]->getBuilding();
			// first check whether the building is not burnt down
			if (!buildingOnFire->isDead()) {
				buildingOnFire->stopFire();
			}
			vecFireTrucksArrived[index]->sendBack();
			buildingOnFire->withdrawFireTruckAssignment();
		}
	}

	// finally, iterate over policetrucks that is arrived
	for (unsigned int index = 0; index < vecPoliceTrucksArrived.size(); index++) {
		if (vecPoliceTrucksArrived[index]->isAtEntranceDepot()) {
			// first check whether it's base is not burnt down
			if (vecPoliceTrucksArrived[index]->getBase()->isDead()) {
				continue;	// stay at the entrance
			}

			// then check whether it's base is on fire or not
			if (vecPoliceTrucksArrived[index]->getBase()->isBurning()) {
				continue;	// then wait for the firetruck
			}
			else {
				vecPoliceTrucksArrived[index]->enterDepot();
			}
		}
		else {	// the police is at a building
			Shop* robbedShop = vecPoliceTrucksArrived[index]->getShop();
			if (!robbedShop->isEmpty()) {
				robbedShop->stopRobbing();
			}
			vecPoliceTrucksArrived[index]->sendBack();
			robbedShop->withdrawPoliceTruckAssignment();
		}
	}
	return true;
}

bool Simulator::repairBuildings() {
	REQUIRE(this->isInitialized(), "Simulator is initialized");
	REQUIRE(this->endSimulation() == false, "Not the end of simulation");

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

	if (vecBuildings.empty()) {
		return false;	// there's no building to repair
	}

	for (unsigned int index = 0; index < vecBuildings.size(); index++) {
		vecBuildings[index]->repair();
	}
	return true;
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
				if (!(*nextTargets.at(randomIndex).second).isDead() ) {
					(*nextTargets.at(randomIndex).second).setFire();
				}
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
				if (!(*nextTargets.at(randomIndex).second).isDead() ){
					(*nextTargets.at(randomIndex).second).setFire();
				}

				int randomIndex2 = rand() % nextTargets.size();
				if (!(*nextTargets.at(randomIndex2).second).isDead() ){
					(*nextTargets.at(randomIndex2).second).setFire();
				}

			}else if(nextTargets.size() == 1){
				int randomIndex = rand() % nextTargets.size();
				if (!(*nextTargets.at(randomIndex).second).isDead() ){
					(*nextTargets.at(randomIndex).second).setFire();
				}

			}
		}
	}
}

void Simulator::step(){
	if (!this->endSimulation()) {
		this->burningDown();
	}

	if (!this->endSimulation()) {
		this->sendFireTrucks();
	}

	if (!this->endSimulation()) {
		this->robbing();
	}

	if (!this->endSimulation()) {
		this->sendPoliceTrucks();
	}

	if (!this->endSimulation()) {
		this->drive();
	}

	if (!this->endSimulation()) {
		this->spreadFire();
	}

	if (!this->endSimulation()) {
		this->repairBuildings();
	}

	(*fOutput).step();
}

void Simulator::step(bool fireSpreading){
	if (!this->endSimulation()) {
		this->burningDown();
	}

	if (!this->endSimulation()) {
		this->sendFireTrucks();
	}

	if (!this->endSimulation()) {
		this->robbing();
	}

	if (!this->endSimulation()) {
		this->sendPoliceTrucks();
	}

	if (!this->endSimulation()) {
		this->drive();
	}

	if(fireSpreading == true){
		if (!this->endSimulation()) {
			this->spreadFire();
		}
	}

	if (!this->endSimulation()) {
		this->repairBuildings();
	}

	(*fOutput).step();
}
