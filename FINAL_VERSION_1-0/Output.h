/*
 * Output.h
 *
 * @author:		Stijn Wouters - 20121136 - stijn.wouters2@student.ua.ac.be
 * @version:	1.0
 * @date:		17 March 2013
 * 
 */

#ifndef OUTPUT_H_
#define OUTPUT_H_

#include <sstream>
#include "DesignByContract.h"
#include "City.h"

class Output {
public:
	bool isInitialized();

	Output(City* town, std::string filename);
	// REQUIRE(town->isInitialized(), "City is initialized");
	// ENSURE(this->isInitialized(), "Output is initialized");

	bool writeToFile();
	// REQUIRE(this->isInitialized(), "Output is initialized");

	bool writeToFile(std::string tokens);
	// REQUIRE(this->isInitialized(), "Output is initialized");

private:
	City* fTown;
	const char* fFileName;

	Output* fMyself;
};

#endif /* OUTPUT_H_ */
