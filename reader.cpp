#include "reader.h"

void reader::openFile(const string& filename)
{
	string holder;
	stringstream converter;
	ifstream input(filename.c_str());
	while(input.good() && input.is_open())
	{
		getline(input, holder);
		converter<<holder;
		converter>>m_contents;
	}
}

string reader::write()
{
	return m_contents;
}
