#include <iostream>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

#ifndef READER_H
#define READER_H

class reader
{
	string m_contents;

	public:

	//reader();

	void openFile(const string& filename);
	vector<reader> parse(const string& delimiter, const string& escape, const string contianerOpen, const string& ContainerClose )const;
	string write();
};

#endif
