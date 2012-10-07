#include "Shape.h"

shape::shape(const vector <ColoredPoint>& triangles)
:m_triangles(triangles),m_lines(),m_points(),more_shapes(),m_leftTransform(ident(3)),m_position(3)
{
}

shape::shape(const string& filename)
:m_triangles(),m_lines(),m_points(),more_shapes(),m_leftTransform(ident(3)),m_position(3)
{
m_leftTransform = math_matrix(ident(3));
m_position = math_vector(3);
}

vector<ColoredPoint> shape::getTriangles()const
{
    return m_triangles;
}

void shape::draw()const
{
    glBegin(GL_TRIANGLES);
    for (unsigned int i = 0; i < m_triangles.size(); i++)
    {
        glColor3d(0.2,0.7,0.9);
        glVertex2d(m_triangles.at(i).position().getValue(0), m_triangles.at(i).position().getValue(1));
    }
    glEnd();
    glBegin(GL_LINES);
    glEnd();
    glBegin(GL_POINTS);
    glEnd();
}

void shape::rotate(const math_matrix& leftTransforMatrix)
{
    m_leftTransform = leftTransforMatrix*m_leftTransform;
}

void shape::translate(const math_vector& displacement)
{
    m_position += displacement;
}
