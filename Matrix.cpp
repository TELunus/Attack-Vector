#include "Matrix.h"

math_matrix::math_matrix(const vector<math_vector>& values)
{
    m_values = values;
    for(unsigned int i = 0; i < num_rows(); i++)
    {
    	//cout<<"m_values["<<i<<"] = "<<m_values.at(i).write()<<endl;
        if (num_collums() != m_values[i].num_elements())
        {
            throw FlexibleExeption("the program tried to create a matrix using a vector of math_vectors of different sizes");
        }
    }
    m_tolerance = 1.0e-6;
}

math_matrix::math_matrix(const vector<vector<double> >& values)
{
    for(unsigned int i = 0; i < values.size(); i++)
    {
        if(math_vector(values[i]).num_elements() == math_vector(values[0]).num_elements())
        {
            m_values.push_back(math_vector(values[i]));
        }
        else
        {
            throw FlexibleExeption("the program tried to create a matrix using a vector of vectors, with different sizes, of doubles");
        }
    }
    m_tolerance = 1.0e-6;
}

void math_matrix::divide_row(const unsigned int& rowIndex, const double& denominator)
{
    if(fabs(denominator) < m_tolerance)
    {
        throw FlexibleExeption("Division by zero in divide_row");
    }
    if (num_rows() > rowIndex)
    {
        m_values[rowIndex] /= denominator;
    }
    else
    {
        std::stringstream errMsg;
        errMsg << "The program tried to divide a row with an invalid row index: row " << rowIndex
        << " in matrix with only " << num_rows() << " rows." << std::endl;
        throw FlexibleExeption(errMsg.str());
    }
}

void math_matrix::multiply_row(const unsigned int& rowIndex, const double& multiplier)
{
    if (num_rows() > rowIndex)
    {
        m_values[rowIndex] *= multiplier;
    }
    else
    {
        throw FlexibleExeption("The program tried to multipy a row with an invalid row index");
    }
}

void math_matrix::add_row(const unsigned int& augend, const unsigned int& addend)
{
    if(augend < num_rows())
    {
        if(addend < num_rows())
        {
            m_values[augend]+=m_values[addend];
        }
        else
        {
            throw FlexibleExeption("The program tried to add a nonexistant row to another row");
        }
    }
    else
    {
        throw FlexibleExeption("The program tried to add a row to a nonexistant row");
    }
}

void math_matrix::subtract_row(const unsigned int& minuend, const unsigned int& subtrahend)
{
    if(subtrahend < num_rows())
    {
        if(minuend < num_rows())
        {
            m_values[minuend]-=m_values[subtrahend];
        }
        else
        {
            throw FlexibleExeption("The program tried to add a nonexistant row to another row");
        }
    }
    else
    {
        throw FlexibleExeption("The program tried to add a row to a nonexistant row");
    }
}

math_matrix math_matrix::drop_row(const unsigned int& index)const
{
    vector <math_vector> new_values(m_values);
    new_values.erase(new_values.begin() + index);
    //for (unsigned int i = 0; i < new_values.size(); i++) debuging lines
    //{
    //	cout<<"new_values ["<<i<<"] = "<<new_values.at(i).write()<<endl;
    //}
    //math_matrix result(new_values);
    //return result;
    return(math_matrix(new_values));
}

math_matrix math_matrix::drop_collum(const unsigned int& index)const
{
    math_matrix new_values(m_values);
    new_values = new_values.transpose();
    new_values = new_values.drop_row(index);
    new_values = new_values.transpose();
    return(new_values);
}

math_vector math_matrix::collum(const unsigned int& index)const
{
	vector<double> result;
	for (unsigned int i = 0; i < num_rows(); i++)
	{
		result.push_back(m_values.at(i).m_values.at(index));
	}
	return math_vector(result);
}

bool math_matrix::is_square()const
{
    bool value = true;
    if(num_rows() != num_collums())
    {
        value = false;
    }
    return value;
}

bool math_matrix::has_inverse()const
{
    bool value = false;
    if(is_square())
    {
        value = true;
        if((determinant() < m_tolerance)&&(determinant() > 0-m_tolerance))
        {
            value = false;
        }
    }
    return value;
}

math_vector math_matrix::operator *(const math_vector& multiplier)const
{
    vector<double> value(m_values.size(),0);
    if(multiplier.num_elements() == num_collums())
    {
        for(unsigned int i = 0; i<m_values.size(); i++)
        {
            value[i] = m_values[i].dot(multiplier);
            //cout<<"value "<<i<<" is "<<value[i]<<endl;
        }
    }
    else
    {
        throw FlexibleExeption("The program tried to multiply a matrix by a vector of a different size");
    }
    return math_vector(value);
}

math_matrix math_matrix::operator *(const math_matrix& multiplier) const//using A*B
{
    math_matrix B = multiplier;//.transpose();
    vector<math_vector> values;
    math_matrix A(m_values);
    //if (A.transpose().m_values.size() == multiplier.m_values.size())
    if(num_collums() == multiplier.num_rows())
    {
        for(unsigned int i = 0; i < m_values.size(); i++)//num_rows()
        {
            vector<double> current_row;
            for(unsigned int j = 0; j < B.m_values.at(0).m_values.size(); j++)//num_collums()
            {
            	//cout<<"A's row "<<i<<" is "<<m_values.at(i).write()<<endl;
            	//cout<<"B's collum "<<j<<" is "<<B.collum(j).write()<<endl;
                current_row.push_back(m_values[i].dot(B.collum(j)));
            }
            values.push_back(math_vector(current_row));
        }
    }
    else
    {
        throw FlexibleExeption("The program tried to multiply a matrix by a matrix of the wrong size");
    }

    return math_matrix(values);
}

unsigned int math_matrix::num_rows()const
{
    return m_values.size();
}

unsigned int math_matrix::num_collums() const
{
    return m_values[0].m_values.size();
}

bool math_matrix::same_size(const math_matrix& refrance)const
{
    bool value = false;
    if((num_rows() == refrance.num_rows())&&(num_collums() == refrance.num_collums()))
    {
        value = true;
    }
    return value;
}

void math_matrix::operator +=(const math_matrix& addend)
{
    if(same_size(addend))
    {
        for(unsigned int i = 0; i < m_values.size(); i++)
        {
            m_values[i] += addend.m_values[i];
        }
    }
    else
    {
        throw FlexibleExeption("The program tried to add a matrix to a matrix of a different size");
    }
}

math_matrix math_matrix::operator +(const math_matrix& addend)const
{
    math_matrix value(m_values);
    if (same_size(addend))
    {
        value += addend;
    }
    else
    {
        throw FlexibleExeption("The program tried to add two matrices of a different sizes");
    }
    return value;
}

void math_matrix::operator -=(const math_matrix& subtrahend)
{
    if (same_size(subtrahend))
    {
        for(unsigned int i = 0; i < m_values.size(); i++)
        {
            m_values[i] -= subtrahend.m_values[i];
        }
    }
    else
    {
        throw FlexibleExeption("The program tried to subtract a matrix from a matrix of a different size");
    }
}

math_matrix math_matrix::operator -(const math_matrix& subtrahend)const
{
    math_matrix value(m_values);
    if (same_size(subtrahend))
    {
        value -= subtrahend;
    }
    else
    {
        throw FlexibleExeption("The program tried to subract two matrices of a different sizes");
    }
    return value;
}

math_matrix math_matrix::inverse()const
{
    math_matrix inverse = ident(m_values.size());
    cout<<inverse.write();
    math_matrix accountant(m_values);
    cout<<accountant.write();
    if(is_square())
    {
        if(has_inverse())
        {
            for(unsigned int i = 0; i<m_values.size(); i++) //walk collum by collum
            {
                double diagonal_element = accountant.m_values[i].m_values[i];
                while((diagonal_element <= m_tolerance) && (diagonal_element >= (-1*m_tolerance)) )
                {
                    int rondom_value = rand()%num_rows();
                    accountant.m_values[i]+=accountant.m_values[rondom_value];
                    accountant.m_values[i]+=accountant.m_values[rondom_value];
                    diagonal_element = accountant.m_values[i].m_values[i];
                }

                accountant.divide_row(i,diagonal_element);//make sure diagonal element in this collum is a 1
                inverse.divide_row(i,diagonal_element);

                for(unsigned int j = 0; j<m_values.size(); j++) //walk row by row
                {
                    double ith_element = accountant.m_values[j].m_values[i];
                    if((ith_element >= m_tolerance) || (ith_element <= (-1*m_tolerance) ) )
                    {
                        accountant.divide_row(j,accountant.m_values[j].m_values[i]);//devide row by its element from this collum
                        inverse.divide_row(j,accountant.m_values[j].m_values[i]);
                        if(i != j)//if we are not dealing with an element on a diagonal
                        {
                            accountant.m_values[j]-=accountant.m_values[j];//subtract the row on that has a diagonal in this collum from this row
                            inverse.m_values[j]-=accountant.m_values[j];
                            //accountant.subtract_row(j,i);
                            //inverse.subtract_row(j,i);
                        }
                    }
                }
            }
        }
        else
        {
            throw FlexibleExeption("The program tried to take the inverese of a matrix with determinant 0");
        }
    }
    else
    {
        throw FlexibleExeption("The program tried to take the inverse of a non-square matrix");
    }

    return inverse;
}

double math_matrix::determinant()const
{
    unsigned int mat_size = num_rows();
    double det = 0;
    if(is_square())
    {
        if(mat_size == 2)
        {
            det += (m_values[0].m_values[0]) * (m_values[1].m_values[1]);
            det -= (m_values[1].m_values[0]) * (m_values[0].m_values[1]);
        }
        else
        {
            for(unsigned int i = 0; i < mat_size; i++)
            {
                if(i % 2 == 0)
                {
                	//double result = m_values.at(0).m_values.at(i);//debugging lines
                	//math_matrix nextMatrix = drop_row(0).drop_collum(i);
                	//det += result*nextMatrix.determinant();
                    det += (m_values[0].m_values[i]) * drop_row(0).drop_collum(i).determinant();
                }
                else
                {
                    det += (m_values[0].m_values[i]) * drop_row(0).drop_collum(i).determinant();
                }
            }
        }
    }
    else
    {
        throw FlexibleExeption("The program tried to take the determinant of a non-square matrix");
    }
    return det;
}

math_matrix math_matrix::transpose()const
{
    vector<math_vector> values;
    for(unsigned int i = 0; i < m_values[0].m_values.size(); i++)//walk collum by collum
    {
        vector<double> input_collum;//collum of this, row of transpose
        for(unsigned int j = 0; j < m_values.size(); j++)//walk row by row
        {
            input_collum.push_back(m_values[j].m_values[i]);
        }
        math_vector output_row(input_collum);//create row of transpose from collum of this
        values.push_back(output_row);
    }

    return math_matrix(values);
}


template <typename Stream>
Stream & operator << (Stream & str, const math_vector& input)
{
    //str<<input.get_value(0);
    //for (int i = 1; i < input.size(); i++)
    //{
    //str<<", "<<input.get_value(i);
    //}
    str<<input.write();
    return str;
}

string math_matrix::write()const
{
    stringstream value;
    value<<endl;
    for(unsigned int i = 0;  i < m_values.size(); i++)
    {
        value<<m_values[i]<<endl;//
    }
    return value.str();
}

math_matrix ident(const unsigned int& size)
{
    vector<double> empty(size,0);
    vector <vector<double> > value(size,empty);
    for(unsigned int i = 0; i < size; i++)
    {
        value[i][i] = 1;
    }
    return math_matrix(value);
}



math_matrix leftRotationMatrix(const math_vector& CircuimferentialDisplacement, const math_vector& Position)
{
	vector<math_vector> result;
	unsigned int size = Position.num_elements();
	math_matrix IdentityMatrix(ident(size));
	for (unsigned int i = 0; i<size; i++)
	{

		math_vector col_i(vector<double>(size, 1.0));
		col_i = IdentityMatrix*col_i;
		math_vector X(Position);
		math_vector Y(X.perpendicular(CircuimferentialDisplacement));
		double theta = Y.magnatude() / X.magnatude();
		X = X/X.magnatude();
		Y = Y/Y.magnatude();

		math_vector perp(X.perpendicular(col_i));
		perp = Y.perpendicular(perp);
		math_vector u_in(X.parallel(col_i));
		math_vector v_in(Y.parallel(col_i));
		math_vector u_out(u_in*cos(theta));
		math_vector v_out(v_in*cos(theta));
		u_out -= v_in*sin(theta);
		v_out += u_in*sin(theta);
		math_vector in_plane(u_out + v_out);
		result.push_back(in_plane + perp);
	}
	return math_matrix(result);
}

math_matrix leftRotMatrix(const math_vector& offset, const math_vector& displacement)
{
    vector<math_vector> result;
    int size = offset.num_elements();
    for (int i = 0; i < size; i++)
    {
        vector<double> next;
        for(int j=0; j<size; j++)
        {
            if(i==j)
            {
                next.push_back(1);
            }
            else
            {
                next.push_back(0);
            }
        }
        result.push_back(math_vector(next).rotate(offset,displacement));
    }
    return (math_matrix(result)).transpose();
}
