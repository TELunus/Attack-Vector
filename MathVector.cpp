#include "MathVector.h"

math_vector::math_vector(int VectorSize)
:m_values(VectorSize,0)
{
    //m_values = vector <double> (VectorSize,0);
}

math_vector::math_vector(const vector<double> & values)
:m_values(values)
{
    //m_values = values;
}

unsigned int math_vector::num_elements()const
{
    return m_values.size();
}

double math_vector::dot(const math_vector& multiplier)const
{
    double value = 0;
    if(num_elements() == multiplier.num_elements())
    {
        for(unsigned int i = 0; i<m_values.size(); i++)
        {
            value+=(m_values[i] * multiplier.m_values[i]);
        }
    }
    else
    {
        throw FlexibleExeption("program tried to take the dot product of two mismached vectors");
    }
    return value;
}

double math_vector::magnatude()const
{
    double value = 0;
    for(unsigned int i = 0; i< m_values.size(); i++)
    {
        value +=(m_values[i]*m_values[i]);
    }
    value = sqrt(value);
    return value;
}

double math_vector::along(const math_vector& source)const
{
	return (((source.magnatude()) != 0) ? ((source.dot(*this))/source.magnatude()) : 0);
}

math_vector math_vector::parallel(const math_vector& source)const
{
	math_vector result(source);
	//cout<<"parallel"<<endl;
	/*
	math_vector result(m_values);
	if(magnatude() != 0)
	{
        result *= (dot(source)/(magnatude()*magnatude()));
	}
	else
	{
	    result *= 0;
	}
	*/
	if(source.magnatude() != 0)
	{
        result *= (source.dot(*this)/(source.magnatude()*source.magnatude()));
	}
	else
	{
	    result *= 0;
	}
	//cout<<"input: "<<source.write()<<"		me:"<<write()<<"		output: "<<source.write()<<endl<<endl;
return source;
}

math_vector math_vector::perpendicular(const math_vector& source)const
{
	//cout<<"perpendicular"<<endl;
	//math_vector result(*this - source.parallel(*this));
	math_vector result(*this - parallel(source));
	//cout<<"input: "<<source.write()<<"		me:"<<write()<<"		output: "<<result.write()<<endl<<endl;
	return result;
}


void math_vector::operator /= (const double& denomerator)
{
    for(unsigned int i = 0; i < m_values.size(); i++)
    {
        m_values[i] /= denomerator;
    }
}

math_vector math_vector::operator / (const double& denomerator)const
{
    math_vector value(m_values);
    value /= denomerator;
    return value;
}

void math_vector::operator *= (const double& multiplier)
{
    for(unsigned int i = 0; i < m_values.size(); i++)
    {
        m_values[i] *= multiplier;
    }
}

math_vector math_vector::operator * (const double& multiplier)const
{
    math_vector value(m_values);
    value *=(multiplier);
    return value;
}

void math_vector::operator += (const math_vector& addend)
{
    if(num_elements() == addend.num_elements())
    {
        for(unsigned int i = 0; i < m_values.size(); i++)
        {
            m_values[i] += addend.m_values[i];
        }
    }
    else
    {
        throw FlexibleExeption("program tried to add a vector to a vector of a different size");
    }
}

math_vector math_vector::operator + (const math_vector& addend)const
{
    math_vector value(m_values);
    if(num_elements() == addend.num_elements())
    {
        value += addend;
    }
    else
    {
        throw FlexibleExeption("program tried to add two vectors of different sizes");
    }
    return value;
}

void math_vector::operator -= (const math_vector& subtrahend)
{
    if(num_elements() == subtrahend.num_elements())
    {
        for(unsigned int i = 0; i < m_values.size(); i++)
        {
            m_values[i] -= subtrahend.m_values[i];
        }
    }
    else
    {
        throw FlexibleExeption("program tried to subtract a vector from a vector of a different size");
    }
}

math_vector math_vector::operator - (const math_vector& subtrahend)const
{
    math_vector value(m_values);
    if(num_elements() == subtrahend.num_elements())
    {
        value -= subtrahend;
    }
    else
    {
        throw FlexibleExeption("program tried to subtract two vectors of different sizes");
    }
    return value;
}


string math_vector::write() const
{
    stringstream value;
    value<<m_values[0];
    for (unsigned int i = 1; i < m_values.size(); i++)
    {
        value<<", "<<m_values[i];
    }
    return value.str();
}

double math_vector::getValue(const int& index)const
{

    return m_values.at(index);
}

math_vector math_vector::rotate(const math_vector& offset, const math_vector& displacement)const
{
    cout<<"rotate"<<endl;
    double theta = (displacement.perpendicular(offset).magnatude())/(offset.magnatude());
    theta /= 10;

	math_vector X_unit = offset/offset.magnatude();
	cout<<"X unit: "<<X_unit.write()<<endl;

	math_vector Y_unit = displacement.perpendicular(offset);
	Y_unit /= Y_unit.magnatude();
	cout<<"Y unit: "<<Y_unit.write()<<endl;

	cout<<"X: ";
    //double X ((parallel(X_unit)).magnatude());
    double X(along(X_unit));
    cout<<X<<endl;
    cout<<"Y: ";
    //double Y ((parallel(Y_unit)).magnatude());
    double Y(along(Y_unit));
    cout<<Y<<endl;
    //cout<<"Z"<<endl;
    math_vector Z(perpendicular(offset).perpendicular(displacement));

    math_vector u = X_unit*(X*cos(theta) - Y*sin(theta));
    math_vector v = Y_unit*(Y*cos(theta) + X*sin(theta));
    //math_vector w = Z;
    math_vector result((u+v)+Z);

    cout<<"input: "<<write()<<"    offset: "<<offset.write()<<"    displacement: "<<displacement.write()<<endl;
    cout<<"theta: "<<theta<<endl;
//    cout<<"X: "<<X.write()<<"    Y: "<<Y.write()<<"    Z: "<<Z.write()<<endl;
    cout<<"u: "<<u.write()<<"    v: "<<v.write()<<"    w: "<<Z.write()<<endl;
    cout<<"output: "<<result.write()<<endl;
    cout<<"magnatude: "<<result.magnatude()<<endl<<endl;

    return result;//since w = Z
}

//math_vector operator "M" (char const* literal)//will not work before C++11 user defined literals are implemented
//{
//	stringstream ss(literal);
//	vector<double> vect;
//	unsigned int length = literal.size();
//	for(unsigned int i = 0; i < length; i++)
//	{
//		double next;
//		ss>>next;
//		vect.push_back(next);
//	}
//	return math_vector(vect);
//}
