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

bool Simulator::isInitialized() {
	return this == Simulator::fMyself;
}

Simulator::Simulator(City* town) {
	REQUIRE(town->isInitialized(), "City is initialized");

	Simulator::fMyself = this;
	Simulator::fTown = town;
	Simulator::fEndSimulation = false;

	ENSURE(this->isInitialized(), "Simulator is initialized");
}

bool Simulator::endSimulation() {
	REQUIRE(this->isInitialized(), "Simulator is initialized");
	return Simulator::fEndSimulation;
}

bool Simulator::fireBreaksOut() {
	REQUIRE(this->isInitialized(), "Simulator is initialized");

	std::vector<Building*> buildings = Simulator::fTown->getBuildings();

	int index = std::rand() % buildings.size();

	if ( (buildings[index]->isBurning() ) || (buildings[index]->isDead() ) ) {
		return false;	// building is already on fire
	}

	buildings[index]->setFire();
	return true;
}

bool Simulator::burningDown(int factor) {
	REQUIRE(this->isInitialized(), "Simulator is initialized");
	REQUIRE(factor > 0, "burning factor is greater than 0");

	std::vector<Building*> buildings = Simulator::fTown->getBuildings();
	for (unsigned int index=0; index < buildings.size(); index++) {
		if (buildings[index]->isBurning() ) {
			buildings[index]->burningDown(factor);
		}
	}

	return true;
}

bool Simulator::drive(int repeat) {
	REQUIRE(this->isInitialized(), "Simulator is initialized");
	REQUIRE(repeat > 0, "repeat at least 1");

	for (int i=0; i < repeat; i++) {
		std::vector<Vehicle*> vehicles = Simulator::fTown->getVehicles();
		std::vector<Street*> verticals = Simulator::fTown->getVerticals();
		std::vector<Street*> horizontals = Simulator::fTown->getHorizontals();

		for (unsigned int index=0; index < vehicles.size(); index++) {
			if (vehicles[index]->isArrived() ) {
				continue;
			}

			Point destination = vehicles[index]->getDestination();
			Point curPos = vehicles[index]->getPosition();

			bool foundDestStr = false;
			Street* destStr;
			for (unsigned int h=0; h < horizontals.size(); h++) {
				if (horizontals[index]->isElement(destination) ) {
					destStr = horizontals[index];
					foundDestStr = true;
					break;
				}
			}

			if (!foundDestStr) {
				for (unsigned int index=0; index < verticals.size(); index++) {
					if (verticals[index]->isElement(destination) ) {
						destStr = verticals[index];
						foundDestStr = true;
						break;
					}
				}
			}

			if (destStr->isElement(curPos) ) {
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

			Street* curStr;
			if (destStr->isHorizontal() ) {	// first search for a crossing street
				bool foundCurStr = false;
				for (unsigned int index=0; index < verticals.size(); index++) {
					if (verticals[index]->isElement(curPos) ) {
						curStr = verticals[index];
						foundCurStr = true;
						break;
					}
				}

				if (!foundCurStr) {
					for (unsigned int index=0; index < horizontals.size(); index++) {
						if (horizontals[index]->isElement(curPos) ) {
							curStr = horizontals[index];
							foundCurStr = true;
							break;
						}
					}
				}
			}

			if (isParallel(*curStr, *destStr) ) {
				Point* cp = Simulator::fTown->closestCrosspoint(*curStr, curPos);
				if (curStr->isVertical()) {
					if (curPos.getY() < cp->getY() ) {
						vehicles[index]->goUp();
					}
					vehicles[index]->goDown();
				}
				else {	// cur str is horizontal
					if (curPos.getX() < cp->getX() ) {
						vehicles[index]->goRight();
					}
					vehicles[index]->goLeft();
				}
			}

			if ( (Simulator::fTown->isCrosspoint(curPos) ) || (isCrossing(*curStr, *destStr) ) ) {
				if (destStr->isHorizontal()) {
					Point* cp = findCrossPoint(*curStr, *destStr);
					if (curStr->isVertical()) {
						if (curPos.getY() < cp->getY() ) {
							vehicles[index]->goUp();
						}
						vehicles[index]->goDown();
					}
					else {	// cur str is horizontal
						if (curPos.getX() < cp->getX() ) {
							vehicles[index]->goRight();
						}
						vehicles[index]->goLeft();
					}
				}
				else {
					Point* cp = findCrossPoint(*curStr, *destStr);
					if (curStr->isVertical()) {
						if (curPos.getY() < cp->getY() ) {
							vehicles[index]->goUp();
						}
						vehicles[index]->goDown();
					}
					else {	// cur str is horizontal
						if (curPos.getX() < cp->getX() ) {
							vehicles[index]->goRight();
						}
						vehicles[index]->goLeft();
					}
				}
			}
		}
	}

	return true;
}

bool Simulator::extinguish() {

	std::vector<FireDepot*> depots = Simulator::fTown->getFireDepots();
	for (unsigned int index=0; index < depots.size(); index++) {
		depots[index]->extinguish();
	}
	return true;
}

bool Simulator::updateTrucks() {

	std::vector<FireDepot*> depots = Simulator::fTown->getFireDepots();
	for (unsigned int index=0; index < depots.size(); index++) {
		depots[index]->updateTrucks();
	}
	return true;
}

bool Simulator::sendTrucks() {

	std::vector<Building*> buildings = Simulator::fTown->getBuildings();
	std::vector<FireDepot*> depots = Simulator::fTown->getFireDepots();

	for (unsigned int index=0; index < buildings.size(); index++) {
		if (!buildings[index]->isBurning()) {
			continue;
		}

		bool alreadySend = false;
		for (unsigned int i=0; i < depots.size(); i++) {
			if (depots[i]->alreadySend( buildings[index]->getLocation() ) ) {
				alreadySend = true;
				break;
			}
		}

		if (alreadySend) {
			continue;	// go to the next house, a firetruck is on the way
		}

		// else we will send a firetruck;
		for (unsigned int i=0; i < depots.size(); i++) {
			if (depots[i]->getAvailableTrucks() > 0) {
				Point p = buildings[index]->getLocation();
				int originX = p.getX();
				int originY = p.getY();

				if ( !Simulator::fTown->isInMap(p) ) {
					int y = p.getY() + 1;
					p.set(originX, y);
				}
				if ( !Simulator::fTown->isInMap(p) ) {
					int x = p.getX() - 1;
					p.set(x, originY);
				}
				if ( !Simulator::fTown->isInMap(p) ) {
					int x =  originX + buildings[index]->getSize().getWidth();
					p.set(x, originY);
				}
				if ( !Simulator::fTown->isInMap(p) ) {
					int y = originY - buildings[index]->getSize().getHeight();
					p.set(originX, y);
				}

				depots[i]->sendTruck(p, buildings[index]);
				break;
			}
		}
	}

	return true;
}
