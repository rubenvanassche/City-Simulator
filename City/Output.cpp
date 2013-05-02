/*
 * Output.cpp
 *
 *  Created on: 29 apr. 2013
 *      Author: Ruben
 */

#include "Output.h"

Output::Output(City* town, char filename[]){
	REQUIRE((*town).isInitialized(), "City is initialized");

	fTown = town;
	fMyself = this;

	// Create a new file
	fFile.open(filename, std::ios_base::out);
	fFile.close();
	fFile.open(filename, std::ios_base::app);

	ENSURE(this->fTown = town, "Town is set");
	ENSURE(FileTest::fileExists(filename), "Empty file made");
	ENSURE(this->isInitialized(), "Output is initialized");
}

std::ostream& operator<< (std::ostream& stream, Output& o){
	REQUIRE(o.isInitialized(), "Ouput is initialized");

	stream << o.get();
	return stream;
}

bool Output::isInitialized() const {
	return fMyself == this;
}


void Output::shopsOnFire(){
	REQUIRE((*fTown).isInitialized(), "City is initialized");
	REQUIRE(this->isInitialized(), "Output is initialized");

	std::vector<Shop*> shops = this->fTown->getShops();
	for(unsigned int i = 0;i < shops.size();i++){
		if(shops.at(i)->isBurning()){
			this->fOut << "Winkel op locatie " << shops.at(i)->getLocation() << " staat in brand en heeft nog " << shops.at(i)->getHealth() << " HP.\n";
		}
	}
}
void Output::housesOnFire(){
	REQUIRE((*fTown).isInitialized(), "City is initialized");
	REQUIRE(this->isInitialized(), "Output is initialized");

	std::vector<House*> houses = this->fTown->getHouses();
	for(unsigned int i = 0;i < houses.size();i++){
		if(houses.at(i)->isBurning()){
			this->fOut << "Huis op locatie " << houses.at(i)->getLocation() << " staat in brand en heeft nog " << houses.at(i)->getHealth() << " HP.\n";
		}
	}
}
void Output::fireDepotsOnFire(){
	REQUIRE((*fTown).isInitialized(), "City is initialized");
	REQUIRE(this->isInitialized(), "Output is initialized");

	std::vector<FireDepot*> fireDepots = this->fTown->getFireDepots();
	for(unsigned int i = 0;i < fireDepots.size();i++){
		if(fireDepots.at(i)->isBurning()){
			this->fOut << "Brandweerkazerne op locatie " << fireDepots.at(i)->getLocation() << " staat in brand en heeft nog " << fireDepots.at(i)->getHealth() << " HP.\n";
		}
	}
}
void Output::policeDepotsOnFire(){
	REQUIRE((*fTown).isInitialized(), "City is initialized");
	REQUIRE(this->isInitialized(), "Output is initialized");

	std::vector<PoliceDepot*> policeDepots = this->fTown->getPoliceDepots();
	for(unsigned int i = 0;i < policeDepots.size();i++){
		if(policeDepots.at(i)->isBurning()){
			this->fOut << "PolitieKantoor op locatie " << policeDepots.at(i)->getLocation() << " staat in brand en heeft nog " << policeDepots.at(i)->getHealth() << " HP.\n";
		}
	}
}
void Output::hospitalsOnFire(){
	REQUIRE((*fTown).isInitialized(), "City is initialized");
	REQUIRE(this->isInitialized(), "Output is initialized");

	std::vector<Hospital*> hospitals = this->fTown->getHospitals();
	for(unsigned int i = 0;i < hospitals.size();i++){
		if(hospitals.at(i)->isBurning()){
			this->fOut << "Ziekenhuis op locatie " << hospitals.at(i)->getLocation() << " staat in brand en heeft nog " << hospitals.at(i)->getHealth() << " HP.\n";
		}
	}
}

void Output::shopsBeingRobbed(){
	REQUIRE((*fTown).isInitialized(), "City is initialized");
	REQUIRE(this->isInitialized(), "Output is initialized");

	std::vector<Shop*> shops = this->fTown->getShops();
	for(unsigned int i = 0;i < shops.size();i++){
		if(shops.at(i)->isRobbing()){
			this->fOut << "Winkel op locatie " << shops.at(i)->getLocation() << " word overvallen en heeft nog " << shops.at(i)->getSecurity() << " RP.\n";
		}
	}
}

void Output::fireTrucksdriving(){
	REQUIRE((*fTown).isInitialized(), "City is initialized");
	REQUIRE(this->isInitialized(), "Output is initialized");

	std::vector<FireTruck*> trucks = this->fTown->getFireTrucks();
	for(unsigned int i = 0;i < trucks.size();i++){
		if(trucks.at(i)->isOnWay()){
			Street* currentStreet;
			if(this->fTown->findStreet(trucks.at(i)->getPosition(), kHORIZONTAL) == NULL){
				currentStreet = this->fTown->findStreet(trucks.at(i)->getPosition(), kVERTICAL);
			}else{
				currentStreet = this->fTown->findStreet(trucks.at(i)->getPosition(), kHORIZONTAL);
			}

			this->fOut << trucks.at(i)->getName() << " op locatie " << trucks.at(i)->getPosition() << " in de " << currentStreet->getName() << " onderweg naar " << trucks.at(i)->getDestination() << " \n";
		}
	}
}

void Output::policeTrucksDriving(){
	REQUIRE((*fTown).isInitialized(), "City is initialized");
	REQUIRE(this->isInitialized(), "Output is initialized");

	std::vector<PoliceTruck*> trucks = this->fTown->getPoliceTrucks();
	for(unsigned int i = 0;i < trucks.size();i++){
		if(trucks.at(i)->isOnWay()){
			Street* currentStreet;
			if(this->fTown->findStreet(trucks.at(i)->getPosition(), kHORIZONTAL) == NULL){
				currentStreet = this->fTown->findStreet(trucks.at(i)->getPosition(), kVERTICAL);
			}else{
				currentStreet = this->fTown->findStreet(trucks.at(i)->getPosition(), kHORIZONTAL);
			}

			this->fOut << trucks.at(i)->getName() << " op locatie " << trucks.at(i)->getPosition() << " in de " << currentStreet->getName() << " onderweg naar " << trucks.at(i)->getDestination() << " \n";
		}
	}
}

void Output::ambulancesDriving(){
	REQUIRE((*fTown).isInitialized(), "City is initialized");
	REQUIRE(this->isInitialized(), "Output is initialized");

	std::vector<Ambulance*> trucks = this->fTown->getAmbulances();
	for(unsigned int i = 0;i < trucks.size();i++){
		if(trucks.at(i)->isOnWay()){
			Street* currentStreet;
			if(this->fTown->findStreet(trucks.at(i)->getPosition(), kHORIZONTAL) == NULL){
				currentStreet = this->fTown->findStreet(trucks.at(i)->getPosition(), kVERTICAL);
			}else{
				currentStreet = this->fTown->findStreet(trucks.at(i)->getPosition(), kHORIZONTAL);
			}

			this->fOut << trucks.at(i)->getName() << " op locatie " << trucks.at(i)->getPosition() << " in de " << currentStreet->getName() << " onderweg naar " << trucks.at(i)->getDestination() << " \n";
		}
	}
}

void Output::fireDepotsTrucks(){
	REQUIRE((*fTown).isInitialized(), "City is initialized");
	REQUIRE(this->isInitialized(), "Output is initialized");

	std::vector<FireDepot*> depots = this->fTown->getFireDepots();
	std::vector<FireTruck*> trucks = this->fTown->getFireTrucks();

	for(unsigned int i = 0;i < depots.size();i++){
		this->fOut << "Beschikbare brandweerwagens in " << depots.at(i)->getName() << " :\n";

		bool notrucks = true;

		for(unsigned int j = 0;j < trucks.size();j++){
			if(trucks.at(j)->getBase() == depots.at(i)){
				if(trucks.at(j)->isOnWay() == false){
					notrucks = false;
					this->fOut << trucks.at(j)->getName() << "\n";
				}
			}
		}

		if(notrucks == true){
			this->fOut << "geen\n";
		}
	}
}
void Output::policeDepotsTrucks(){
	REQUIRE((*fTown).isInitialized(), "City is initialized");
	REQUIRE(this->isInitialized(), "Output is initialized");

	std::vector<PoliceDepot*> depots = this->fTown->getPoliceDepots();
	std::vector<PoliceTruck*> trucks = this->fTown->getPoliceTrucks();

	for(unsigned int i = 0;i < depots.size();i++){
		this->fOut << "Beschikbare politiewagens in " << depots.at(i)->getName() << " :\n";

		bool notrucks = true;

		for(unsigned int j = 0;j < trucks.size();j++){
			if(trucks.at(j)->getBase() == depots.at(i)){
				if(trucks.at(j)->isOnWay() == false){
					notrucks = false;
					this->fOut << trucks.at(j)->getName() << "\n";
				}
			}
		}

		if(notrucks == true){
			this->fOut << "geen\n";
		}
	}
}
void Output::hospitalsTrucks(){
	REQUIRE((*fTown).isInitialized(), "City is initialized");
	REQUIRE(this->isInitialized(), "Output is initialized");

	std::vector<Hospital*> depots = this->fTown->getHospitals();
	std::vector<Ambulance*> trucks = this->fTown->getAmbulances();

	for(unsigned int i = 0;i < depots.size();i++){
		this->fOut << "Beschikbare ziekenwagens in " << depots.at(i)->getName() << " :\n";

		bool notrucks = true;

		for(unsigned int j = 0;j < trucks.size();j++){
			if(trucks.at(j)->getBase() == depots.at(i)){
				if(trucks.at(j)->isOnWay() == false){
					notrucks = false;
					this->fOut << trucks.at(j)->getName() << "\n";
				}
			}
		}

		if(notrucks == true){
			this->fOut << "geen\n";
		}
	}
}

void Output::shopsRepairing(){
	REQUIRE((*fTown).isInitialized(), "City is initialized");
	REQUIRE(this->isInitialized(), "Output is initialized");

	std::vector<Shop*> buildings = this->fTown->getShops();
	for(unsigned int i = 0;i < buildings.size();i++){
		if(buildings.at(i)->startRepair()){
			this->fOut << "Winkel op locatie " << buildings.at(i)->getLocation() << " is zichzelf aan het herstellen, " << buildings.at(i)->getHealth() << " HP.\n";
		}
	}
}


void Output::housesRepairing(){
	REQUIRE((*fTown).isInitialized(), "City is initialized");
	REQUIRE(this->isInitialized(), "Output is initialized");

	std::vector<House*> buildings = this->fTown->getHouses();
	for(unsigned int i = 0;i < buildings.size();i++){
		if(buildings.at(i)->startRepair()){
			this->fOut << "Huis op locatie " << buildings.at(i)->getLocation() << " is zichzelf aan het herstellen, " << buildings.at(i)->getHealth() << " HP.\n";
		}
	}
}


void Output::fireDepotsRepairing(){
	REQUIRE((*fTown).isInitialized(), "City is initialized");
	REQUIRE(this->isInitialized(), "Output is initialized");

	std::vector<FireDepot*> buildings = this->fTown->getFireDepots();
	for(unsigned int i = 0;i < buildings.size();i++){
		if(buildings.at(i)->startRepair()){
			this->fOut << "Brandweerkazerne op locatie " << buildings.at(i)->getLocation() << " is zichzelf aan het herstellen, " << buildings.at(i)->getHealth() << " HP.\n";
		}
	}
}


void Output::policeDepotsRepairing(){
	REQUIRE((*fTown).isInitialized(), "City is initialized");
	REQUIRE(this->isInitialized(), "Output is initialized");

	std::vector<PoliceDepot*> buildings = this->fTown->getPoliceDepots();
	for(unsigned int i = 0;i < buildings.size();i++){
		if(buildings.at(i)->startRepair()){
			this->fOut << "Politiebureau op locatie " << buildings.at(i)->getLocation() << " is zichzelf aan het herstellen, " << buildings.at(i)->getHealth() << " HP.\n";
		}
	}
}


void Output::HospitalsRepairing(){
	REQUIRE((*fTown).isInitialized(), "City is initialized");
	REQUIRE(this->isInitialized(), "Output is initialized");

	std::vector<Hospital*> buildings = this->fTown->getHospitals();
	for(unsigned int i = 0;i < buildings.size();i++){
		if(buildings.at(i)->startRepair()){
			this->fOut << "Ziekenhuis op locatie " << buildings.at(i)->getLocation() << " is zichzelf aan het herstellen, " << buildings.at(i)->getHealth() << " HP.\n";
		}
	}
}


void Output::parse(){
	REQUIRE(this->isInitialized(), "Output is initialized");

	fOut << "Events:\n";

	this->shopsOnFire();
	this->housesOnFire();
	this->fireDepotsOnFire();
	this->policeDepotsOnFire();
	this->hospitalsOnFire();

	this->shopsBeingRobbed();

	fOut << "\nVoertuigen onderweg:\n";

	this->fireTrucksdriving();
	this->policeTrucksDriving();
	this->ambulancesDriving();

	fOut << "\nVoertuigen in stations:\n";

	this->fireDepotsTrucks();
	this->policeDepotsTrucks();
	this->hospitalsTrucks();

	fOut << "\nGebouwen die gerepareerd worden:\n";

	this->shopsRepairing();
	this->housesRepairing();
	this->fireDepotsRepairing();
	this->policeDepotsRepairing();
	this->HospitalsRepairing();

	fOut << "\n\n\n";
}

std::string Output::get(){
	REQUIRE(this->isInitialized(), "Output is initialized");

	fOut.str(""); // clean the Out stream

	this->parse();
	std::string output = this->fOut.str();
	return output;
}

void Output::step(){
	REQUIRE(this->isInitialized(), "Output is initialized");

	fOut.str(""); // clean the Out stream
	this->parse();
	fFile << fOut.str(); // Write to the fileStream
}

void Output::write(){
	REQUIRE(this->isInitialized(), "Output is initialized");

	this->fFile.close();
}

Output::~Output(){
	REQUIRE(this->isInitialized(), "Output is initialized");

	this->fFile.close();
}

