#include "Camera.h"

camera::camera()
:m_position(3),m_anti_transform(ident(3)),m_fieldOfView(45),m_scale(1),m_perspective(true),m_dots(),m_lines(),m_triangles()
{

}

camera::camera(const math_vector& pos, const math_matrix& anti_transform, const double& size, const bool& perspective)
:m_position(pos),m_anti_transform(anti_transform),m_fieldOfView(size),m_scale(size),m_perspective(perspective),m_dots(),m_lines(),m_triangles()
{

}

void camera::insert(const shape& nextShape)
{
    vector<ColoredPoint> input(nextShape.getTriangles());
    m_triangles.insert( m_triangles.end(), input.begin(), input.end() );
}

void camera::clear()
{
    m_dots.clear();
    m_lines.clear();
    m_triangles.clear();
}

void camera::draw()const
{
    glBegin(GL_TRIANGLES);
    //glBegin(GL_POINTS);//debuging line
    for (unsigned int i = 0; i < m_triangles.size(); i++)
    {
        math_vector PointPos = m_triangles.at(i).position();
        cout<<"before: "<<PointPos.write()<<endl;
        PointPos = convert(PointPos);
        glColor3d(0.2,0.7,0.9);
        glVertex2d(PointPos.getValue(0), PointPos.getValue(1));
        cout<<"after: "<<PointPos.write()<<endl;
        //cout<<PointPos.getValue(0)<<", "<<PointPos.getValue(1)<<" ";
        //cout<<m_anti_transform.write();
    }
    //cout<<"got here"<<endl;
    glEnd();
    /*
    glBegin(GL_TRIANGLES);

    glColor3f(1.0f, 0.0f, 0.0f);   glVertex2f(0.0f,   1.0f);
    glColor3f(0.0f, 1.0f, 0.0f);   glVertex2f(0.87f,  -0.5f);
    glColor3f(0.0f, 0.0f, 1.0f);   glVertex2f(-0.87f, -0.5f);
    glEnd();
    */
    glBegin(GL_LINES);
    glEnd();
    glBegin(GL_POINTS);//
    glEnd();
}

math_vector camera::convert(const math_vector& input)const
{
    math_vector output(input);
    //cout<<output.getValue(0)<<", "<<output.getValue(1)<<" ";
    output -= m_position;
    output = m_anti_transform*output;
    if(m_perspective == false)
    {
        output = output*m_scale;
    }
    return output;
}

void camera::rotate(const math_vector& displacement,const math_vector& offset)
{
	//cout<<"rotate"<<endl<<"displacement: "<<displacement.write()<<endl;
    math_vector antidisplacement = displacement*(-1);
    //cout<<"antidisplacement: "<<antidisplacement.write()<<endl;
    math_matrix change = leftRotMatrix(offset, antidisplacement);
    m_anti_transform = change*m_anti_transform;
    cout<<change.write();
    cout<<m_anti_transform.write();
}
