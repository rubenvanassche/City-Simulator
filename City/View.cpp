#include "View.h"

void View::print(std::string out){
	std::cout << out;
}

void View::print(std::string out, bool newliner){
	std::cout << out;

	if(newliner == true){
		std::cout << std::endl;
	}
}


void View::print(int out){
	std::cout << out;
}

void View::print(int out, bool newliner){
	std::cout << out;

	if(newliner == true){
		std::cout << std::endl;
	}
}

void View::print(double out){
	std::cout << out;
}

void View::print(double out, bool newliner){
	std::cout << out;

	if(newliner == true){
		std::cout << std::endl;
	}
}

void View::newline(){
	std::cout << std::endl;
}