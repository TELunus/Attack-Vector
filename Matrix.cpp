#include "Matrix.h"
#include "Utils.h"

/*
Some thoughts on class design.
* Consistency - sometimes methods modifying underlying, other times they return a new matrix
* Error messages should include argument values when argument values are source of problem
* Precondition checks at beginning
* All shops I've worked at use camel case instead of _ for method names
* operator== very useful for unit testing
*/

math_matrix::math_matrix(const vector<math_vector>& values):m_rows(values),m_tolerance(1.0e-6)
{
    for(unsigned int i = 0; i < num_rows(); i++)
    {
        if (num_collums() != m_rows[i].num_elements())
        {
            throw FlexibleExeption("the program tried to create a matrix using a vector of math_vectors of different sizes");
        }
    }
}

math_matrix::math_matrix(const vector<vector<double> >& values):m_rows(),m_tolerance(1.0e-6)
{
    for(unsigned int i = 0; i < values.size(); i++)
    {
        if(math_vector(values[i]).num_elements() == math_vector(values[0]).num_elements())
        {
            m_rows.push_back(math_vector(values[i]));
        }
        else
        {
            throw FlexibleExeption("the program tried to create a matrix using a vector of vectors, with different sizes, of doubles");
        }
    }
}

bool math_matrix::operator==( const math_matrix & rhs) const
{
	if( num_rows() != rhs.num_rows()) return false;
	for( unsigned int i=0; i < rhs.num_rows(); i++)
	{
		if( ! (m_rows[i] == rhs.m_rows[i])) return false;

	}
	return true;
}

void math_matrix::divide_row(const unsigned int& rowIndex, const double& denominator)
{
    if(fabs(denominator) < m_tolerance)
    {
        throw FlexibleExeption("Division by zero in divide_row");
    }
    if (num_rows() > rowIndex)
    {
        m_rows[rowIndex] /= denominator;
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
        m_rows[rowIndex] *= multiplier;
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
            m_rows[augend]+=m_rows[addend];
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
            m_rows[minuend]-=m_rows[subtrahend];
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

math_matrix math_matrix::drop_row( unsigned int index)const
{
    if( index >= num_rows() )
	{
		stringstream errMsg;
		errMsg << "Trying to drop row " << index << "in matrix with only " << num_rows() << " rows.";
		throw FlexibleExeption(errMsg.str());
	}
	vector <math_vector> new_values(m_rows);
    new_values.erase(new_values.begin() + index);

    return(math_matrix(new_values));
}

math_matrix math_matrix::drop_collum(const unsigned int& index)const
{
    math_matrix new_values(m_rows);
    new_values = new_values.transpose();
    new_values = new_values.drop_row(index);
    new_values = new_values.transpose();
    return(new_values);
}

math_vector math_matrix::collum(const unsigned int& index)const
{
	if( index >= num_rows() )
	{
		stringstream errMsg;
		errMsg << "Trying to extract column " << index << " in matrix with only " << num_rows() << " columns.";
		throw FlexibleExeption(errMsg.str());
	}

	vector<double> result;
	for (unsigned int i = 0; i < num_rows(); i++)
	{
		result.push_back(m_rows.at(i).m_values.at(index));
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
		double det = determinant();
        if(( det< m_tolerance)&&(det > 0-m_tolerance))
        {
            value = false;
        }
    }
    return value;
}

math_vector math_matrix::operator *(const math_vector& multiplier)const
{
    vector<double> value(m_rows.size(),0);
    if(multiplier.num_elements() == num_collums())
    {
        for(unsigned int i = 0; i<m_rows.size(); i++)
        {
            value[i] = m_rows[i].dot(multiplier);
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
    math_matrix A(m_rows);
    if(num_collums() == multiplier.num_rows())
    {
        for(unsigned int i = 0; i < m_rows.size(); i++)//num_rows()
        {
            vector<double> current_row;
            for(unsigned int j = 0; j < B.m_rows.at(0).m_values.size(); j++)//num_collums()
            {
                current_row.push_back(m_rows[i].dot(B.collum(j)));
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
    return m_rows.size();
}

unsigned int math_matrix::num_collums() const
{
    return m_rows[0].num_elements();
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
        for(unsigned int i = 0; i < m_rows.size(); i++)
        {
            m_rows[i] += addend.m_rows[i];
        }
    }
    else
    {
        throw FlexibleExeption("The program tried to add a matrix to a matrix of a different size");
    }
}

math_matrix math_matrix::operator +(const math_matrix& addend)const
{
    math_matrix value(m_rows);
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
        for(unsigned int i = 0; i < m_rows.size(); i++)
        {
            m_rows[i] -= subtrahend.m_rows[i];
        }
    }
    else
    {
        throw FlexibleExeption("The program tried to subtract a matrix from a matrix of a different size");
    }
}

math_matrix math_matrix::operator -(const math_matrix& subtrahend)const
{
    math_matrix value(m_rows);
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
    math_matrix result = ident(m_rows.size());
    cout<<result.write();
    math_matrix accountant(m_rows);
    cout<<accountant.write();
    if(is_square())
    {
        if(has_inverse())
        {
            for(unsigned int i = 0; i<m_rows.size(); i++) //walk collum by collum
            {
                double diagonal_element = accountant.m_rows[i].m_values[i];
                while((diagonal_element <= m_tolerance) && (diagonal_element >= (-1*m_tolerance)) )
                {
                    int rondom_value = rand()%num_rows();
                    accountant.m_rows[i]+=accountant.m_rows[rondom_value];
                    accountant.m_rows[i]+=accountant.m_rows[rondom_value];
                    diagonal_element = accountant.m_rows[i].m_values[i];
                }

                accountant.divide_row(i,diagonal_element);//make sure diagonal element in this collum is a 1
                result.divide_row(i,diagonal_element);

                for(unsigned int j = 0; j<m_rows.size(); j++) //walk row by row
                {
                    double ith_element = accountant.m_rows[j].m_values[i];
                    if((ith_element >= m_tolerance) || (ith_element <= (-1*m_tolerance) ) )
                    {
                        accountant.divide_row(j,accountant.m_rows[j].m_values[i]);//devide row by its element from this collum
                        result.divide_row(j,accountant.m_rows[j].m_values[i]);
                        if(i != j)//if we are not dealing with an element on a diagonal
                        {
                            accountant.m_rows[j]-=accountant.m_rows[j];//subtract the row on that has a diagonal in this collum from this row
                            result.m_rows[j]-=accountant.m_rows[j];
                            //accountant.subtract_row(j,i);
                            //result.subtract_row(j,i);
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

    return result;
}

double math_matrix::determinant()const
{
    unsigned int mat_size = num_rows();
    double det = 0;
    if(is_square())
    {
        if(mat_size == 2)
        {
            det += (m_rows[0].m_values[0]) * (m_rows[1].m_values[1]);
            det -= (m_rows[1].m_values[0]) * (m_rows[0].m_values[1]);
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
                    det += (m_rows[0].m_values[i]) * drop_row(0).drop_collum(i).determinant();
                }
                else
                {
                    det -= (m_rows[0].m_values[i]) * drop_row(0).drop_collum(i).determinant();
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
    for(unsigned int i = 0; i < m_rows[0].m_values.size(); i++)//walk collum by collum
    {
        vector<double> input_collum;//collum of this, row of transpose
        for(unsigned int j = 0; j < m_rows.size(); j++)//walk row by row
        {
            input_collum.push_back(m_rows[j].m_values[i]);
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
    for(unsigned int i = 0;  i < m_rows.size(); i++)
    {
        value<<m_rows[i]<<endl;//
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
