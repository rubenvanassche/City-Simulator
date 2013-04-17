/*
 * Check.cpp
 *
 *  Created on: 25 mrt. 2013
 *      Author: Ruben
 */

#include "Check.h"

Check::Check(){
	Check::fMyself = this;
}

bool Check::isInitialized() {
	return this == Check::fMyself;
}

bool Check::go(Building& building){
	std::vector<Point*> newPoints = building.calculatePoints();
	std::vector<Point*>::iterator it;

	bool checked = true;

	if(this->checkPoints(newPoints)){
		this->addPoints(newPoints, 'b');
	}else{
		checked = false;
	}

	for(it = newPoints.begin();it != newPoints.end();it++){
		//delete *it;
	}


	return checked;
}
bool Check::go(Street& street){
	std::vector<Point*> newPoints = street.calculatePoints();
	std::vector<Point*>::iterator it;

	bool checked = true;

	if(this->checkStreetPoints(newPoints)){
		this->addPoints(newPoints, 's');
	}else{
		checked = false;
	}

	for(it = newPoints.begin();it != newPoints.end();it++){
		//delete *it;
	}

	return checked;
}


bool Check::checkPoints(std::vector<Point*> newPoints){
	std::vector<Point*>::iterator it;

	for(it = newPoints.begin();it != newPoints.end();++it){
		if(this->checkPoint(**it) == false){
			return false;
		}
	}

	return true;
}

bool Check::checkPoint(Point& p){
	std::vector<Point*>::iterator it;

	for(it = fUsedPoints.begin();it != fUsedPoints.end();++it){
		if(p == **it){
			return false;
		}
	}

	return true;
}

bool Check::checkStreetPoints(std::vector<Point*> newPoints){
	std::vector<Point*>::iterator it;

	for(it = newPoints.begin();it != newPoints.end();++it){
		if(this->checkStreetPoint(**it) == false){
			return false;
		}
	}

	return true;
}

bool Check::checkStreetPoint(Point& p){
	for(unsigned int i = 0;i < fUsedPoints.size();i++){
		if(p == *(fUsedPoints.at(i))){
			if(fUsedPointTypes.at(i) != 's'){
				return false;
			}
		}
	}

	return true;
}


void Check::addPoints(std::vector<Point*> newPoints, char type){
	std::vector<Point*>::iterator it;

	for(it = newPoints.begin();it != newPoints.end();++it){
		fUsedPoints.push_back(*it);
		fUsedPointTypes.push_back(type);
	}

}

Check::~Check() {
	fUsedPoints.clear();
	fUsedPointTypes.clear();
}

