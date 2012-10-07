#include "ColoredPoint.h"
#include <gl/gl.h>
#include "Matrix.h"

#ifndef SHAPE_H
#define SHAPE_H
class shape
{
    vector <ColoredPoint> m_triangles;
    vector <ColoredPoint> m_lines;
    vector <ColoredPoint> m_points;
    vector <shape> more_shapes;
    math_matrix m_leftTransform;
    math_vector m_position;
    public:
    shape(const vector <ColoredPoint>& triangles);
    shape (const string& filename);
    vector<ColoredPoint> getTriangles()const;
    void rotate(const math_matrix& leftTransformMatrix);
    void translate(const math_vector& displacement);
    void draw()const;
};
#endif
