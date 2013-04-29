#include "Out.h"

Out::Out(const std::string &filename){
	Out::fMyself = this;
	Out::fFileName = filename.c_str();
	Out::fIndent = false;

	// Create a new file
	Out::filestream.open(Out::fFileName, std::ios_base::out);
	Out::filestream.close();
	Out::filestream.open(Out::fFileName, std::ios_base::app);
}

bool Out::isInitialized() const {
	return this == Out::fMyself;
}


template <class T>
Out& Out::operator<<(T& v){
	this->indentHere();
	Out::filestream << v;
	return *this;
}
Out& Out::operator<<(const int& v){
	this->indentHere();
	Out::filestream << v;
	return *this;
}
Out& Out::operator<<(const double& v){
	this->indentHere();
	Out::filestream << v;
	return *this;
}
Out& Out::operator<<(const char v[]){
	this->indentHere();
	Out::filestream << v;
	return *this;
}
Out& Out::operator<<(Point& p) {
	this->indentHere();
	Out::filestream << p;
	return *this;
}
std::string Out::endl(){
	return "\n";
}



bool Out::indent(){
	if(fIndent == true){
		fIndent = false;
	}else{
		fIndent = true;
	}

	return fIndent;
}

bool Out::indent(const bool& yes){
	if(yes == true){
		fIndent = true;
	}else{
		fIndent = false;
	}

	return fIndent;
}

bool Out::isIndenting(){
	return fIndent;
}

void Out::writeFile(){
	Out::filestream.close();
	Out::filestream.open(Out::fFileName, std::ios_base::app);
}

void Out::newFile(){
	Out::filestream.close();
	Out::filestream.open(Out::fFileName, std::ios_base::out);
	Out::filestream.close();
	Out::filestream.open(Out::fFileName, std::ios_base::app);
}

void Out::indentHere(){
	if(fIndent == true){
		Out::filestream << "    ";
	}
}

void Out::get(){
	std::cout << this->filestream << std::endl;
}

Out::~Out(){
	Out::filestream << "\n\n\n\n--------------\n";
	Out::filestream << "City-Simulator\n";
	Out::filestream << "--------------\n";
	Out::filestream.close();
}
