#include "ship.h"
//using namespace std;
ship::ship(const string& filename)
:m_shape(vector<ColoredPoint>(0,ColoredPoint(0,0,0,0,0,0)))
{
	vector<double> inital_pos(3);

	ifstream configfile(filename.c_str());
	configfile>>inital_pos.at(0)>>inital_pos.at(1)>>inital_pos.at(2);
	vector<ColoredPoint> ship_shape;
	vector<double> point(6);
	while(configfile.good())
	{
		for(unsigned int i = 0; (i < 6)&&(configfile.good()); i++)
		{
			configfile>>point.at(i);
			if (i == 5)
			{
				ship_shape.push_back(ColoredPoint(point.at(0),point.at(1),point.at(2),point.at(3),point.at(4),point.at(5)));
			}
		}

	}
	m_shape = shape(ship_shape);
	m_shape.translate(math_vector(inital_pos));

}

ship::~ship()
{

}
