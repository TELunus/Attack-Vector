#ifndef CAMERA_H
#define CAMERA_H

#include "Matrix.h"
#include "ColoredPoint.h"
#include "Shape.h"
#include <gl/gl.h>

class camera
{
    math_vector m_position;
    math_matrix m_anti_transform;
    double m_fieldOfView;//for perspective
    double m_scale;//for orthografic
    bool m_perspective;
    vector<ColoredPoint> m_dots;
    vector<ColoredPoint> m_lines;
    vector<ColoredPoint> m_triangles;

    math_vector convert(const math_vector& input)const;

    public:

    camera();
    camera(const math_vector& pos, const math_matrix& anti_transform, const double& size, const bool& perspective);

    void insert(const shape& nextShape);
    void clear();
    void draw()const;

    void rotate(const math_vector& displacement,const math_vector& offset);
};
#endif
