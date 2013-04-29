#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>
#include "FileTest.h"

TEST(FileTestTest, FileCompare) {
	ASSERT_TRUE(FileTest::directoryExists("testOutput"));

	ofstream myfile;
	myfile.open("testOutput/file1.txt");
	myfile.close();
	myfile.open("testOutput/file2.txt");
	myfile.close();

	//compare 2 empty files
// *** Beware: the following does not work with older versions of libstdc++
// *** It doesn't work with gcc version 4.0.1 (Apple Inc. build 5465)
// *** It does work with gcc version 4.2.1
//	EXPECT_TRUE(FileCompare("testOutput/file1.txt", "testOutput/file2.txt"));
//	EXPECT_TRUE(FileCompare("testOutput/file2.txt", "testOutput/file1.txt"));

	//compare an empty and a non-empty files
	myfile.open("testOutput/file1.txt");
	myfile << "xxx" << endl << "yyy";
	myfile.close();
	EXPECT_FALSE(FileTest::compare("testOutput/file1.txt", "testOutput/file2.txt"));
	EXPECT_FALSE(FileTest::compare("testOutput/file2.txt", "testOutput/file1.txt"));

	//compare two equal files
	myfile.open("testOutput/file2.txt");
	myfile << "xxx" << endl << "yyy";
	myfile.close();
	EXPECT_TRUE(FileTest::compare("testOutput/file1.txt", "testOutput/file2.txt"));
	EXPECT_TRUE(FileTest::compare("testOutput/file2.txt", "testOutput/file1.txt"));

	//compare 2 non-empty files which are off by a character in the middle
	myfile.open("testOutput/file2.txt");
	myfile << "xxx" << endl << "xyy";
	myfile.close();
	EXPECT_FALSE(FileTest::compare("testOutput/file1.txt", "testOutput/file2.txt"));
	EXPECT_FALSE(FileTest::compare("testOutput/file2.txt", "testOutput/file1.txt"));

	//compare 2 non-empty files where one is one character shorter than the other
	myfile.open("testOutput/file2.txt");
	myfile << "xxx" << endl << "yy";
	myfile.close();
	EXPECT_FALSE(FileTest::compare("testOutput/file1.txt", "testOutput/file2.txt"));
	EXPECT_FALSE(FileTest::compare("testOutput/file2.txt", "testOutput/file1.txt"));

	//compare existig against non existing file
	EXPECT_FALSE(FileTest::compare("testOutput/file1.txt", "testOutput/nonexisting.txt"));
	EXPECT_FALSE(FileTest::compare("testOutput/nonexisting.txt", "testOutput/file1.txt"));
}

TEST(FileTestTest, fileExists){
	ofstream myfile;
	myfile.open("testOutput/file1.txt");
	myfile.close();
	myfile.open("testOutput/file2.txt");
	myfile.close();

	EXPECT_TRUE(FileTest::fileExists("testOutput/file1.txt"));
	EXPECT_TRUE(FileTest::fileExists("testOutput/file2.txt"));
	EXPECT_FALSE(FileTest::fileExists("testOutput/file3.txt"));
}
