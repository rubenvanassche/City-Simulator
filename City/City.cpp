/*
 * City.cpp
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	2.0
 * @date:		Friday 26 April 2013
 * 
 */

#include "City.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

bool City::isInitialized() const {
	return fMyself == this;
}


std::ostream& operator<< (std::ostream& stream, City& c) {
	REQUIRE(c.isInitialized(), "City is initialized");

	stream << c.print();
	return stream;
}


City::City() {

	fMyself = this;

	ENSURE(this->isInitialized(), "City is initialized");
}

City::~City() {
	REQUIRE(this->isInitialized(), "City is initialized");

	for (unsigned int index = 0; index < fFireDepots.size(); index++) {
		delete fFireDepots[index];
	}
	fFireDepots.clear();

	for (unsigned int index = 0; index < fPoliceDepots.size(); index++) {
		delete fPoliceDepots[index];
	}
	fPoliceDepots.clear();

	for (unsigned int index = 0; index < fHospitals.size(); index++) {
		delete fHospitals[index];
	}
	fHospitals.clear();

	for (unsigned int index = 0; index < fShops.size(); index++) {
		delete fShops[index];
	}
	fShops.clear();

	for (unsigned int index = 0; index < fHouses.size(); index++) {
		delete fHouses[index];
	}
	fHouses.clear();

	for (unsigned int index = 0; index < fHorizontals.size(); index++) {
		delete fHorizontals[index];
	}
	fHorizontals.clear();

	for (unsigned int index = 0; index < fVerticals.size(); index++) {
		delete fVerticals[index];
	}
	fVerticals.clear();

	for (unsigned int index = 0; index < fFireTrucks.size(); index++) {
		delete fFireTrucks[index];
	}
	fFireTrucks.clear();

	for (unsigned int index = 0; index < fPoliceTrucks.size(); index++) {
		delete fPoliceTrucks[index];
	}
	fPoliceTrucks.clear();

	for (unsigned int index = 0; index < fAmbulances.size(); index++) {
		delete fAmbulances[index];
	}
	fAmbulances.clear();

	ENSURE(this->getFireDepots().empty(), "FireDepots empty'd");
	ENSURE(this->getPoliceDepots().empty(), "Policedepots empty'd");
	ENSURE(this->getHospitals().empty(), "Hospitals empty'd");
	ENSURE(this->getShops().empty(), "Shops empty'd");
	ENSURE(this->getHouses().empty(), "Houses empty'd");
	ENSURE(this->getFireTrucks().empty(), "FireTrucks empty'd");
	ENSURE(this->getPoliceTrucks().empty(), "PoliceTrucks empty'd");
	ENSURE(this->getAmbulances().empty(), "Ambulance empty'd");
}

bool City::isDead() {
	REQUIRE(this->isInitialized(), "City is initialized");

	// check whether all buildings were burnt down
	// first check all houses
	for (unsigned int index = 0; index < fHouses.size(); index++) {
		if (fHouses[index]->isDead() ) {
			continue;
		}
		else {
			return false;
		}
	}

	// then check all shops
	for (unsigned int index = 0; index < fShops.size(); index++) {
		if (fShops[index]->isDead()) {
			continue;
		}
		else {
			return false;
		}
	}

	// then check all depots
	for (unsigned int index = 0; index < fPoliceDepots.size(); index++) {
		if (fPoliceDepots[index]->isDead()) {
			continue;
		}
		else {
			return false;
		}
	}

	for (unsigned int index = 0; index < fHospitals.size(); index++) {
		if (fHospitals[index]->isDead()) {
			continue;
		}
		else {
			return false;
		}
	}

	for (unsigned int index = 0; index < fFireDepots.size(); index++) {
		if (fFireDepots[index]->isDead()) {
			continue;
		}
		else {
			return false;
		}
	}

	// if you've reached here, then all buildings were burnt down
	return true;
}

bool City::add(const Street& str) {
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(str.isInitialized(), "Street is initialized");

	if (!fChecker.go(str) ) {
		return false;
	}

	if (str.isVertical()) {
		Street* ptrStreet = new Street(str);
		fVerticals.push_back(ptrStreet);
		return true;
	}
	else if (str.isHorizontal()) {
		Street* ptrStreet = new Street(str);
		fHorizontals.push_back(ptrStreet);
		return true;
	}
	else {
		return false;
	}
}


bool City::add(const FireTruck& truck){
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(truck.isInitialized(), "Truck is initialized");

	FireTruck* ptrTruck = new FireTruck(truck);
	fFireTrucks.push_back(ptrTruck);
	return true;
}

bool City::add(const PoliceTruck& car){
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(car.isInitialized(), "PoliceCar is initialized");

	PoliceTruck* ptrCar = new PoliceTruck(car);
	fPoliceTrucks.push_back(ptrCar);
	return true;
}

bool City::add(const Ambulance& ambulance){
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(ambulance.isInitialized(), "Ambulance is initialized");

	Ambulance* ptrAmbulance = new Ambulance(ambulance);
	fAmbulances.push_back(ptrAmbulance);
	return true;
}

bool City::add(const FireDepot& depot) {
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(depot.isInitialized(), "FireDepot is initialized");

	if (!fChecker.go(depot)) {
		return false;
	}

	FireDepot* ptrDepot = new FireDepot(depot);
	fFireDepots.push_back(ptrDepot);
	return true;
}

bool City::add(const PoliceDepot& depot) {
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(depot.isInitialized(), "PoliceDepot is initialized");

	if (!fChecker.go(depot)) {
		return false;
	}

	PoliceDepot* ptrDepot = new PoliceDepot(depot);
	fPoliceDepots.push_back(ptrDepot);
	return true;
}

bool City::add(const Hospital& depot) {
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(depot.isInitialized(), "Hospital is initialized");

	if (!fChecker.go(depot)) {
		return false;
	}

	Hospital* ptrDepot = new Hospital(depot);
	fHospitals.push_back(ptrDepot);
	return true;
}

bool City::add(const House& house) {
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(house.isInitialized(), "House is initialized");

	if (!fChecker.go(house)) {
		return false;
	}

	House* ptrHouse = new House(house);
	fHouses.push_back(ptrHouse);
	return true;
}

bool City::add(const Shop& shop) {
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(shop.isInitialized(), "Shop is initialized");

	if (!fChecker.go(shop)) {
		return false;
	}

	Shop* ptrShop = new Shop(shop);
	fShops.push_back(ptrShop);
	return true;
}

FireDepot* City::findFireDepot(const std::string& name) {
	REQUIRE(this->isInitialized(), "City is initialized");

	for (unsigned int index = 0; index < fFireDepots.size(); index++) {
		if (fFireDepots[index]->getName() == name) {
			return fFireDepots[index];
		}
	}

	return NULL;
}

Hospital* City::findHospital(const std::string& name) {
	REQUIRE(this->isInitialized(), "City is initialized");

	for (unsigned int index = 0; index < fHospitals.size(); index++) {
		if (fHospitals[index]->getName() == name) {
			return fHospitals[index];
		}
	}

	return NULL;
}

PoliceDepot* City::findPoliceDepot(const std::string& name) {
	REQUIRE(this->isInitialized(), "City is initialized");

	for (unsigned int index = 0; index < fPoliceDepots.size(); index++) {
		if (fPoliceDepots[index]->getName() == name) {
			return fPoliceDepots[index];
		}
	}

	return NULL;
}

std::vector<House*> City::getHouses() const {
	REQUIRE(this->isInitialized(), "City is initialized");
	return fHouses;
}

std::vector<FireDepot*> City::getFireDepots() const{
	REQUIRE(this->isInitialized(), "City is initialized");
	return fFireDepots;
}

std::vector<PoliceDepot*> City::getPoliceDepots() const{
	REQUIRE(this->isInitialized(), "City is initialized");
	return fPoliceDepots;
}

std::vector<Hospital*> City::getHospitals() const {
	REQUIRE(this->isInitialized(), "City is initialized");
	return fHospitals;
}

std::vector<Shop*> City::getShops() const {
	REQUIRE(this->isInitialized(), "City is initialized");
	return fShops;
}

std::vector<FireTruck*> City::getFireTrucks() const {
	REQUIRE(this->isInitialized(), "City is initialized");
	return fFireTrucks;
}

std::vector<PoliceTruck*> City::getPoliceTrucks() const {
	REQUIRE(this->isInitialized(), "City is initialized");
	return fPoliceTrucks;
}

std::vector<Ambulance*> City::getAmbulances() const {
	REQUIRE(this->isInitialized(), "City is initialized");
	return fAmbulances;
}

bool City::isInMap(const Point& p) {
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(p.isInitialized(), "City is initialized");

	for (unsigned int index = 0; index < fVerticals.size(); index++) {
		if (fVerticals[index]->isElement(p)) {
			return true;
		}
	}

	for (unsigned int index = 0; index < fHorizontals.size(); index++) {
		if (fHorizontals[index]->isElement(p)) {
			return true;
		}
	}

	return false;
}

Street* City::findStreet(const Point& position, const EDirection& dir) {
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(position.isInitialized(), "Point is initialized");

	if (dir == kHORIZONTAL) {
		for (unsigned int index = 0; index < fHorizontals.size(); index++) {
			if (fHorizontals[index]->isElement(position)) {
				return fHorizontals[index];
			}
		}

		// if you've reached here, then you have to look up in the verticals
		for (unsigned int index = 0; index < fVerticals.size(); index++) {
			if (fVerticals[index]->isElement(position)) {
				return fVerticals[index];
			}
		}

		return NULL; // if not found
	}
	else if (dir == kVERTICAL) {
		for (unsigned int index = 0; index < fVerticals.size(); index++) {
			if (fVerticals[index]->isElement(position)) {
				return fVerticals[index];
			}
		}

		// if you've reached here, then you have to look up in the horizontals
		for (unsigned int index = 0; index < fHorizontals.size(); index++) {
			if (fHorizontals[index]->isElement(position)) {
				return fHorizontals[index];
			}
		}

		return NULL; // if not found
	}
	else {
		return NULL;
	}
}

Point City::findClosestCrosspoint(const Point& position) {
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(position.isInitialized(), "Point is initialized");
	REQUIRE(this->isInMap(position) == true, "Position is in roadmap");

	// first find the street where you are
	Street* street = this->findStreet(position, kVERTICAL);

	if (street->isVertical()) {
		// then search in the horizontals all streets that is crossing with this street
		std::vector<Point> vecPoints;

		for (unsigned int index = 0; index < fHorizontals.size(); index++) {
			if (street->isCrossing(*fHorizontals[index])) {
				Point crosspoint = street->getCrosspoint(*fHorizontals[index]);
				vecPoints.push_back(crosspoint);
			}
		}

		// then compare it with the current position
		Point crosspoint = vecPoints[0];
		for (unsigned int index = 0; index < vecPoints.size(); index++) {
			int delta0 = abs(crosspoint.getY() - position.getY());
			int delta1 = abs(vecPoints[index].getY() - position.getY() );

			if (delta1 < delta0) {
				// then change the crosspoint
				crosspoint = vecPoints[index];
			}
		}

		return crosspoint;
	}
	else {
		// street is horizontal
		// so find all streets in the verticals that is crossing with this street

		std::vector<Point> vecPoints;

		for (unsigned int index = 0; index < fVerticals.size(); index++) {
			if (street->isCrossing(*fVerticals[index])) {
				Point crosspoint = street->getCrosspoint(*fVerticals[index]);
				vecPoints.push_back(crosspoint);
			}
		}

		// then compare it with the current position
		Point crosspoint = vecPoints[0];
		for (unsigned int index = 0; index < vecPoints.size(); index++) {
			int delta0 = abs(crosspoint.getX() - position.getX());
			int delta1 = abs(vecPoints[index].getX() - position.getX());

			if (delta1 < delta0) {
				// then change the crosspoint
				crosspoint = vecPoints[index];
			}
		}

		return crosspoint;
	}
}

Point City::nextStep(const Point& curPos, const Point& destination) {
	REQUIRE(this->isInitialized(), "City is initialized");
	REQUIRE(curPos.isInitialized(), "Point is initialized");
	REQUIRE(destination.isInitialized(), "Point is initialized");
	REQUIRE(this->isInMap(curPos), "CurPos is in roadmap");
	REQUIRE(this->isInMap(destination), "Destination is in roadmap");

	int x = curPos.getX();
	int y = curPos.getY();

	Street* destStr = this->findStreet(destination, kHORIZONTAL);
	if (destStr->isElement(curPos)) {
		// current position is part of the  destination street
		if (destStr->isVertical()) {
			if (destination.getY() > curPos.getY() ) {
				return Point(x, y + 1);
			}
			else if (destination.getY() < curPos.getY() ) {
				return Point(x, y - 1);
			}

			return curPos;	// you're already on the destination
		}
		else { // destination street is horizontal
			if (destination.getX() > curPos.getX() ) {
				return Point(x + 1, y);
			}
			else if (destination.getX() < curPos.getX()) {
				return Point(x - 1, y);
			}

			return curPos;	// you're already on the destination
		}
	}

	// else, you have to find in which street you are now
	Street* curStr;
	if (destStr->isVertical()) {
		curStr = this->findStreet(curPos, kHORIZONTAL);
	}
	else {
		curStr = this->findStreet(curPos, kVERTICAL);
	}

	if (destStr->isCrossing(*curStr)) {
		// then find the crosspoint
		Point crosspoint = destStr->getCrosspoint(*curStr);
		if (curStr->isVertical()) {
			if (crosspoint.getY() > curPos.getY()) {
				return Point(x, y + 1);
			}
			else if (crosspoint.getY() < curPos.getY() ) {
				return Point(x, y - 1);
			}

			return curPos;
		}
		else {
			if (crosspoint.getX() > curPos.getX() ) {
				return Point(x + 1, y);
			}
			else if (crosspoint.getX() < curPos.getX() ) {
				return Point(x - 1, y);
			}

			return curPos;
		}
	}

	if (destStr->isParallel(*curStr) ) {
		// then find the closest crosspoint
		Point crosspoint = this->findClosestCrosspoint(curPos);
		if (curStr->isVertical()) {
			if (crosspoint.getY() > curPos.getY()) {
				return Point(x, y + 1);
			}
			else if (crosspoint.getY() < curPos.getY()) {
				return Point(x, y - 1);
			}

			return curPos;
		}
		else {
			if (crosspoint.getX() > curPos.getX()) {
				return Point(x + 1, y);
			}
			else if (crosspoint.getX() < curPos.getX()) {
				return Point(x - 1, y);
			}

			return curPos;
		}
	}

	return curPos;
}

std::ostream& City::print(){
	REQUIRE(this->isInitialized(), "City is initialized");

  std::filebuf fb; // No idea why this stands here but it's the only way to make it work
  std::ostream stream(&fb);

  std::vector<Point> fireDepotPoints;
  std::vector<Point> housePoints;
  std::vector<Point> shopPoints;
  std::vector<Point> policeDepotPoints;
  std::vector<Point> hospitalPoints;
  std::vector<Point> policeTruckPoints;
  std::vector<Point> fireTruckPoints;
  std::vector<Point> ambulancePoints;
  std::vector<Point> streetPoints;

  std::vector<Point> burningBuildingPoints;
  std::vector<Point> deadBuildingPoints;
  std::vector<Point> robbingshopPoints;

  // Buildings

  for(unsigned int i = 0;i < fFireDepots.size();i++){
	  std::vector<Point> temp = (*fFireDepots.at(i)).calculatePoints();
	  if((*fFireDepots.at(i)).isBurning()){
		  burningBuildingPoints.insert(burningBuildingPoints.end(), temp.begin(), temp.end() );
	  }else if((*fFireDepots.at(i)).isDead()){
		  deadBuildingPoints.insert(deadBuildingPoints.end(), temp.begin(), temp.end() );
	  }else{
		  fireDepotPoints.insert(fireDepotPoints.end(), temp.begin(), temp.end() );
	  }
  }

  for(unsigned int i = 0;i < fHouses.size();i++){
	  std::vector<Point> temp = (*fHouses.at(i)).calculatePoints();
	  if((*fHouses.at(i)).isBurning()){
		  burningBuildingPoints.insert(burningBuildingPoints.end(), temp.begin(), temp.end() );
	  }else if((*fHouses.at(i)).isDead()){
		  deadBuildingPoints.insert(deadBuildingPoints.end(), temp.begin(), temp.end() );
	  }else{
		  housePoints.insert(housePoints.end(), temp.begin(), temp.end() );
	  }
  }

  for(unsigned int i = 0;i < fShops.size();i++){
	  std::vector<Point> temp = (*fShops.at(i)).calculatePoints();
	  if((*fShops.at(i)).isBurning()){
		  burningBuildingPoints.insert(burningBuildingPoints.end(), temp.begin(), temp.end() );
	  }else if((*fShops.at(i)).isDead()){
		  deadBuildingPoints.insert(deadBuildingPoints.end(), temp.begin(), temp.end() );
	  }else if((*fShops.at(i)).isRobbing()){
		  robbingshopPoints.insert(robbingshopPoints.end(), temp.begin(), temp.end() );
	  }else{
		  shopPoints.insert(shopPoints.end(), temp.begin(), temp.end() );
	  }
  }

  for(unsigned int i = 0;i < fPoliceDepots.size();i++){
	  std::vector<Point> temp = (*fPoliceDepots.at(i)).calculatePoints();
	  if((*fPoliceDepots.at(i)).isBurning()){
		  burningBuildingPoints.insert(burningBuildingPoints.end(), temp.begin(), temp.end() );
	  }else if((*fPoliceDepots.at(i)).isDead()){
		  deadBuildingPoints.insert(deadBuildingPoints.end(), temp.begin(), temp.end() );
	  }else{
		  policeDepotPoints.insert(policeDepotPoints.end(), temp.begin(), temp.end() );
	  }
  }

  for(unsigned int i = 0;i < fHospitals.size();i++){
	  std::vector<Point> temp = (*fHospitals.at(i)).calculatePoints();
	  if((*fHospitals.at(i)).isBurning()){
		  burningBuildingPoints.insert(burningBuildingPoints.end(), temp.begin(), temp.end() );
	  }else if((*fHospitals.at(i)).isDead()){
		  deadBuildingPoints.insert(deadBuildingPoints.end(), temp.begin(), temp.end() );
	  }else{
		  hospitalPoints.insert(hospitalPoints.end(), temp.begin(), temp.end() );
	  }
  }

  // Vehicles

  for(unsigned int i = 0;i < fFireTrucks.size();i++){
	  fireTruckPoints.push_back((*fFireTrucks.at(i)).getPosition());
  }

  for(unsigned int i = 0;i < fPoliceTrucks.size();i++){
	  policeTruckPoints.push_back((*fPoliceTrucks.at(i)).getPosition());
  }

  for(unsigned int i = 0;i < fAmbulances.size();i++){
	  ambulancePoints.push_back((*fAmbulances.at(i)).getPosition());
  }

  // Streets

  for(unsigned int i = 0;i < fVerticals.size();i++){
	  std::vector<Point> temp = (*fVerticals.at(i)).calculatePoints();
	  streetPoints.insert(streetPoints.end(), temp.begin(), temp.end() );
  }

  for(unsigned int i = 0;i < fHorizontals.size();i++){
	  std::vector<Point> temp = (*fHorizontals.at(i)).calculatePoints();
	  streetPoints.insert(streetPoints.end(), temp.begin(), temp.end() );
  }

  // Now determine the size of the map

  Point biggestPoint(0,0);

  for(unsigned int i = 0;i < streetPoints.size();i++){
	  Point refferPoint = streetPoints.at(i);
	  if(refferPoint.getX() > biggestPoint.getX()){
		  biggestPoint.setX(refferPoint.getX());
	  }

	  if(refferPoint.getY() > biggestPoint.getY()){
		  biggestPoint.setY(refferPoint.getY());
	  }
  }

  // Make a vector matrix
  std::vector< std::vector<char> > map;

  for(unsigned int i = 0;i < biggestPoint.getX() + 1;i++){
	  std::vector<char> row;
	  for(unsigned int j = 0;j < biggestPoint.getY() + 1;j++){
		  row.push_back('\0');
	  }
	  map.push_back(row);
  }



  // Put the points in the map

  for(unsigned int i = 0;i < fireDepotPoints.size();i++){
	  Point newPoint = fireDepotPoints.at(i);
	  map.at(newPoint.getX()).at(newPoint.getY()) = 'K';
  }

  for(unsigned int i = 0;i < housePoints.size();i++){
	  Point newPoint = housePoints.at(i);
	  map.at(newPoint.getX()).at(newPoint.getY()) = 'H';
  }

  for(unsigned int i = 0;i < shopPoints.size();i++){
	  Point newPoint = shopPoints.at(i);
	  map.at(newPoint.getX()).at(newPoint.getY()) = 'W';
  }

  for(unsigned int i = 0;i < policeDepotPoints.size();i++){
	  Point newPoint = policeDepotPoints.at(i);
	  map.at(newPoint.getX()).at(newPoint.getY()) = 'P';
  }

  for(unsigned int i = 0;i < hospitalPoints.size();i++){
	  Point newPoint = hospitalPoints.at(i);
	  map.at(newPoint.getX()).at(newPoint.getY()) = 'Z';
  }

  for(unsigned int i = 0;i < burningBuildingPoints.size();i++){
	  Point newPoint = burningBuildingPoints.at(i);
	  map.at(newPoint.getX()).at(newPoint.getY()) = '#';
  }

  for(unsigned int i = 0;i < deadBuildingPoints.size();i++){
	  Point newPoint = deadBuildingPoints.at(i);
	  map.at(newPoint.getX()).at(newPoint.getY()) = 'X';
  }

  for(unsigned int i = 0;i < robbingshopPoints.size();i++){
	  Point newPoint = robbingshopPoints.at(i);
	  map.at(newPoint.getX()).at(newPoint.getY()) = '&';
  }

  for(unsigned int i = 0;i < streetPoints.size();i++){
	  Point newPoint = streetPoints.at(i);
	  map.at(newPoint.getX()).at(newPoint.getY()) = ' ';
  }

  for(unsigned int i = 0;i < fireTruckPoints.size();i++){
	  Point newPoint = fireTruckPoints.at(i);
	  map.at(newPoint.getX()).at(newPoint.getY()) = '*';
  }

  for(unsigned int i = 0;i < policeTruckPoints.size();i++){
	  Point newPoint = policeTruckPoints.at(i);
	  map.at(newPoint.getX()).at(newPoint.getY()) = '%';
  }

  for(unsigned int i = 0;i < ambulancePoints.size();i++){
	  Point newPoint = ambulancePoints.at(i);
	  map.at(newPoint.getX()).at(newPoint.getY()) = '=';
  }

  // now let's add the map to the stream

  for(unsigned int i = 0;i < biggestPoint.getY() + 1;i++){
	  for(unsigned int j = 0;j < biggestPoint.getX() + 1;j++){
		  stream << map.at(j).at(biggestPoint.getY()-i);
		  std::cout <<  map.at(j).at(biggestPoint.getY()-i);
	  }
	  stream << '\n';
	  std::cout << std::endl;
  }

  return stream;
}
