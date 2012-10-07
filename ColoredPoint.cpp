#include "ColoredPoint.h"
ColoredPoint::ColoredPoint(const double& x,const double& y,const double& z,const double& r,const double& g,const double& b)
: m_coords(3), m_x(x), m_y(y), m_z(z), m_r(r), m_g(g), m_b(b)
{
    vector <double> coords(3,0);
    coords.at(0) = x;
    coords.at(1) = y;
    coords.at(2) = z;
    m_coords = math_vector(coords);
}

math_vector ColoredPoint::position()const
{
    return m_coords;
}
