#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include "MathVector.h"

#ifndef MATRIX_H
#define MATRIX_H

using namespace std;

class math_matrix//states are blank(can't fail), failable(needs checking), checkd(needs handler), and handled
{

    public:
        math_matrix(const vector<math_vector>&);//handled
        math_matrix(const vector<vector<double> >&);//handled

        void divide_row(const unsigned int& rowIndex, const double& denominator);//handled
        void multiply_row(const unsigned int&, const double&);//handled
        void add_row(const unsigned int&,const unsigned  int&);//handled
        void subtract_row(const unsigned int&,const unsigned  int&);//handled
        math_matrix drop_row(const unsigned int&)const;
        math_matrix drop_collum(const unsigned int&)const;

        bool is_square()const;
        bool has_inverse()const;
        double determinant()const;//handled
        math_matrix transpose()const;


        math_vector operator *(const math_vector&)const;//handled
        math_matrix operator *(const math_matrix&)const;//handled
        void operator+=(const math_matrix&);//handled
        math_matrix operator +(const math_matrix&)const;//handled
        void operator -=(const math_matrix&);//handled
        math_matrix operator -(const math_matrix&)const;//handled

        math_matrix inverse()const;//handled

        unsigned int num_rows()const;
        unsigned int num_collums()const;
        bool same_size(const math_matrix& )const;
        math_vector collum(const unsigned int& index)const;//failable

        string write()const;
    private:
        vector<math_vector> m_values;
        double m_tolerance;
};

math_matrix ident(const unsigned int&);
math_matrix leftRotationMatrix(const math_vector&, const math_vector&);//failable//broken
math_matrix leftRotMatrix(const math_vector& offset, const math_vector& displacement);
#endif
