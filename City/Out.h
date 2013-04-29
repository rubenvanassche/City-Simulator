/*
 * Out.h

 *
 *  Created on: 20 mrt. 2013
 *      Author: Ruben
 *  TODO
 *  -Tests
 *  -Contracts
 */

#ifndef OUT_H_
#define OUT_H_

#include <iostream>
#include <string>
#include <fstream>
#include "Point.h"

class Out{
public:
    Out(const std::string &filename);

    bool isInitialized() const;

    template <class T>
    Out &operator<<(T &v);
    Out &operator<<(const int &v);
    Out &operator<<(const double &v);
    Out &operator<<(const char v[]);
    Out &operator<<(Point& p);
    std::string endl();

    bool indent();
    bool indent(const bool& yes);
    bool isIndenting();

    void writeFile();

    void newFile();

    void get();

    ~Out();
private:

    void indentHere();

	const char* fFileName;
	Out* fMyself;
	std::ofstream filestream;
	bool fIndent;
};

#endif /* OUT_H_ */
