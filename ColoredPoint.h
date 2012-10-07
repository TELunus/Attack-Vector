#include "Matrix.h"
#ifndef COLOUREDPOINT_H
#define COLOUREDPOINT_H
class ColoredPoint

{
    math_vector m_coords;
    double m_x;
    double m_y;
    double m_z;
    double m_r;
    double m_g;
    double m_b;
    public:
    friend class shape;
    friend class camera;
    ColoredPoint(const double& x,const double& y,const double& z,const double& r,const double& g,const double& b);
    math_vector position()const;
};
#endif
