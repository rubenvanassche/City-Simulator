#include <iostream>
#include <fstream>
#include <sys/stat.h>

/* Based upon the source on the ansymo website */

using namespace std;

namespace FileTest{
	bool fileExists(const char *filename);
	bool directoryExists(const char *dirname);
	bool compare(const char *leftFileName, const char *rightFileName);
}
