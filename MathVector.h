#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>
#include "FlexibleExeption.h"

#ifndef MATHVECTOR_H
#define MATHVECTOR_H
using namespace std;




class math_vector//states are blank(can't fail), failable(needs checking), checkd(needs handler), and handled
{

    public:
        math_vector(int);
        math_vector(const vector<double> &);

        double dot(const math_vector&)const;//handled
        double magnatude()const;
        double along(const math_vector&)const;//failable
        math_vector parallel(const math_vector&)const;//failable
        math_vector perpendicular(const math_vector&)const;//failable
        math_vector rotate(const math_vector& offset,const math_vector& displacement)const;//failable

        void operator /= (const double&);
        math_vector operator / (const double&)const;
        void operator *= (const double&);
        math_vector operator * (const double&)const;
        void operator += (const math_vector&);//handled
        math_vector operator +(const math_vector&)const;//handled
        void operator -= (const math_vector&);//handled
        math_vector operator -(const math_vector&)const;//handled

        string write() const;
        unsigned int num_elements()const;
        double getValue(const int&)const;//failable

		bool operator==(const math_vector & rhs) const;


        friend class math_matrix;
    private:
        vector <double> m_values;
};

//math_vector operator "M" (char const*);//will not work before C++11 user defined literals are implemented

//
//template <typename Stream>
//Stream & operator << (Stream & str, const math_vector& input)
//{
//    str<<input.write();
//return str;
//}
#endif
