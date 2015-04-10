#ifndef SHIP_H
#define SHIP_H

#include "Shape.h"
#include <iostream>
#include <fstream>
class ship
{
    //math_vector m_position;
    //math_matrix m_rotation;//
    shape m_shape;

    public:

	ship(const string& filename);
	virtual ~ship();
    virtual void update ()=0;
};


#endif // SHIP_H
