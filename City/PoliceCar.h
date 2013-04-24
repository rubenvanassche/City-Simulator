/*
 * PoliceCar.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	
 * @date:		
 * 
 */

#ifndef POLICECAR_H_
#define POLICECAR_H_

#include "EmergencyCar.h"

class PoliceCar: public EmergencyCar {
public:
	bool isInitialized() const;
	// checks whether the object is initialized properly

	friend std::ostream& operator<< (std::ostream& stream, PoliceCar& f);
	// output operator overloading
	// REQUIRE(f.isInitialized(), "PoliceCar is initialized");

	PoliceCar(const std::string& name, Depot* base);
	// constructor
	// ENSURE(this->isInitialized(), "PoliceCar is initialized");

	PoliceCar(const PoliceCar& f);
	// copy constructor
	// REQUIRE(f.isInitialized(), "PoliceCar is initialized");
	// ENSURE(this->isInitialized(), "PoliceCar is initialized");

	void operator= (const PoliceCar& f);
	// copy by assignment
	// REQUIRE(f.isInitialized(), "PoliceCar is initialized");
	// REQUIRE(this->isInitialized(), "PoliceCar is initialized");
	// ENSURE(this->isInitialized(), "PoliceCar is initialized");

	char getSymbol();
	/* Returns the symbol of this instance in the city to be used with the graphical impression */

private:
	PoliceCar* fMyself;
};

#endif /* POLICECAR_H_ */
