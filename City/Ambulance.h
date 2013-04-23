/*
 * Ambulance.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	
 * @date:		
 * 
 */

#ifndef AMBULANCE_H_
#define AMBULANCE_H_

#include "EmergencyCar.h"
#include "Building.h"


class Ambulance: public EmergencyCar {
public:
	bool isInitialized() const;
	// checks whether the object is initialized properly

	friend std::ostream& operator<< (std::ostream& stream, Ambulance& f);
	// output operator overloading
	// REQUIRE(f.isInitialized(), "Ambulance is initialized");

	Ambulance(const std::string& name, Depot* base);
	// constructor
	// ENSURE(this->isInitialized(), "Ambulance is initialized");

	Ambulance(const Ambulance& f);
	// copy constructor
	// REQUIRE(f.isInitialized(), "Ambulance is initialized");
	// ENSURE(this->isInitialized(), "Ambulance is initialized");

	void operator= (const Ambulance& f);
	// copy by assignment
	// REQUIRE(f.isInitialized(), "Ambulance is initialized");
	// REQUIRE(this->isInitialized(), "Ambulance is initialized");
	// ENSURE(this->isInitialized(), "Ambulance is initialized");

private:
	Ambulance* fMyself;
};

#endif /* AMBULANCE_H_ */
