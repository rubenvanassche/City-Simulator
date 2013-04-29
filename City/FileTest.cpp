#include "FileTest.h"

bool FileTest::fileExists(const char *filename){
	// via : http://www.cplusplus.com/forum/general/1796/
	ifstream ifile(filename);
	return ifile;
}

bool FileTest::directoryExists(const char *dirname) {
	struct stat st;
	return stat(dirname, &st) == 0;
}

bool FileTest::compare(const char *leftFileName, const char *rightFileName) {
	ifstream leftFile, rightFile;
	char leftRead, rightRead;
	bool result;

	// Open the two files.
	leftFile.open(leftFileName);
	if (!leftFile.is_open()) {
		return false;
	};
	rightFile.open(rightFileName);
	if (!rightFile.is_open()) {
		leftFile.close();
		return false;
	};

	result = true; // files exist and are open; assume equality unless a counterexamples shows up.
	while (result && leftFile.good() && rightFile.good()) {
		leftFile.get(leftRead);
		rightFile.get(rightRead);
		result = (leftRead == rightRead);
	};
	if (result) {
		 // last read was still equal; are we at the end of both files ?
		result = (!leftFile.good()) && (!rightFile.good());
	};

	leftFile.close();
	rightFile.close();
	return result;
}
