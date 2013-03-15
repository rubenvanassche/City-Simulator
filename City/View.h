#include <vector>
#include <string>
#include <iostream>

class View{
public:
	void print(std::string out);
	void print(std::string out, bool newliner);
	void print(int out);
	void print(int out, bool newliner);
	void print(double out);
	void print(double out, bool newliner);
	void newline();
};