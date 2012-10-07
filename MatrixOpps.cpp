#include <iostream>
#include <vector>
#include <math.h>
#include "Matrix.h"
using namespace std;


template <typename Stream>
Stream & operator << (Stream & str, const math_vector& input)
{
    str<<input.write();
    return str;
}

int main()
{
	try
	{

    vector <double> foo;
    foo.push_back(-1);
    foo.push_back(0);
    foo.push_back(0);
    math_vector first(foo);
    cout<<"first is "<<first<<endl;

    foo[0] = 0;
    foo[1] = 10;
    foo[2] = 0;
    math_vector second(foo);
    cout<<"second is "<<second<<endl;
    foo[0] = 0;
    foo[1] = 0;
    foo[2] = 11;
    math_vector third(foo);
    cout<<"third is "<<third<<endl;


    vector <math_vector> bar ;
    bar.push_back(first);
    bar.push_back(second);
    bar.push_back(third);
//math_matrix test_mat(bar);
    math_matrix test_mat = ident(4);
    cout<<"test matrix is "<<test_mat.write();
    math_matrix inverted = test_mat.inverse();
    cout<<", its inverse is"<<inverted.write();
    double det = test_mat.determinant();
    cout<<"and its determinant is "<<det<<endl;

    math_vector test_vect = (first*10.0 + second/3.0 + third +third*-5);
    cout<<"test vector is "<<test_vect<<" test_vect dot test_vect = "<<test_vect.dot(test_vect)<<endl;
    cout<<"magnatude of testvector is "<<test_vect.magnatude()<<endl;
    bool gotException = false;
    try
    {
        test_vect = test_mat*test_vect;
    }
    catch(const FlexibleExeption & multExcep)
    {
        gotException = true;
        //cout<<"got expected exception"
    }
    if (!gotException)
    {
    	cout << "Did not get the expected exception";
    }
    //assert(gotException);
    math_matrix ident3 = ident(3);
    test_vect = ident3 * test_vect;

    cout<<"test vector is "<<test_vect<<endl;


    test_mat.divide_row(2,5);
    test_mat.multiply_row(1,2);
    test_mat.add_row(0,2);
    cout<<"test matrix is "<<test_mat.write();
    cout<<"and its transpose is "<<test_mat.transpose().write();
    cout<<"test matrix * identity is "<<(test_mat*ident(4)).write();

	vector<double> oset;
	oset.push_back(0);
	oset.push_back(1);
	oset.push_back(0);
	math_vector offset(oset);

    vector<double> disp;
	disp.push_back(1);
	disp.push_back(0);
	disp.push_back(0);
    math_vector displacemet(disp);

    vector<double> test_u;
	test_u.push_back(1);
	test_u.push_back(0);
	test_u.push_back(0);
    math_vector test_x(test_u);

    test_x.rotate(offset,displacemet);

    math_matrix transform = leftRotMatrix(offset,displacemet);
    cout<<endl<<"transform is: "<<transform.write();

	math_vector X = displacemet;
	math_vector Y = offset;

	cout<<"X transformed becomes: "<<(transform*X).write()<<endl;
	cout<<"Y transformed becomes: "<<(transform*Y).write()<<endl;

    vector<vector<double> > rows;
    vector<double> collum;
    collum.push_back(0);
    collum.push_back(0);
    collum.push_back(0);
    rows.push_back(collum);
    rows.push_back(collum);
    rows.push_back(collum);
    rows.at(0).at(0) = 1;
    rows.at(1).at(1) = 1;
    rows.at(2).at(2) = 1;
    rows.at(0).at(1) = -1;
    rows.at(1).at(0) = 1;
    math_matrix it(rows);
    it = transform;
    cout<<" it is "<<it.write()<<endl;
    cout<<" it*it is "<<(it*it).write()<<endl;

    cout<<"enter an interger return status, 0 for sucsess, other for failure"<<endl;

    int status;
    cin>>status;
    return status;
    }
    catch(FlexibleExeption err)
    {
    	cout<<err.what();
    }
    catch(...)
    {
    	cout<<"unknown exeption thrown";
    }
}
