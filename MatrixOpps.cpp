#include <iostream>
#include <vector>
#include <cmath>

#include "Matrix.h"
#include "Utils.h"

using namespace std;

#define checkExceptionThrown1Arg(exceptionType, objname, fname, arg1) { \
    bool macroGotException = false;			\
    try {									\
        objname.fname( (arg1) );			\
    }										\
    catch(const exceptionType & macroExcep) \
    {										\
        macroGotException = true;			\
    }										\
    checkCondition(macroGotException); }
	
#define checkExceptionThrown2Args(exceptionType, objname, fname, arg1, arg2) { \
    bool macroGotException = false;			\
    try {									\
        objname.fname( (arg1), (arg2));		\
    }										\
    catch(const exceptionType & macroExcep) \
    {										\
        macroGotException = true;			\
    }										\
    checkCondition(macroGotException); }



template <typename Stream>
Stream & operator << (Stream & str, const math_vector& input)
{
    str<<input.write();
    return str;
}

void checkCondition(bool condition)
{
    if(! condition )
	{
        throw;
	}
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
	checkCondition(feq(first.magnatude(), 1.0));

    foo[0] = 0;
    foo[1] = 10;
    foo[2] = 0;
    math_vector second(foo);
	checkCondition(feq(second.magnatude()*second.magnatude(), second.dot(second)) );
	checkCondition(feq(second.dot(first), 0));

    foo[0] = 0;
    foo[1] = 0;
    foo[2] = 11;
    math_vector third(foo);
    checkCondition( feq(third.magnatude()* third.magnatude(), third.dot(third)));
	checkCondition(feq(third.dot(first), 0));
	checkCondition(feq(third.dot(second),0));


    vector <math_vector> bar ;
    bar.push_back(first);
    bar.push_back(second);
    bar.push_back(third);
	math_matrix bar_mat(bar);
	
    math_matrix test_mat = ident(4);
    checkCondition(feq(test_mat.determinant(), 1.0));
	checkCondition(!(test_mat == bar_mat));
	
	
    math_matrix inverted = test_mat.inverse();
	checkCondition(feq(inverted.determinant(), 1.0));
	checkCondition(test_mat == inverted);

    math_vector test_vect = (first*10.0 + second/3.0 + third +third*-5);
	double dotProduct = test_vect.dot(test_vect);
    cout<<"test vector is "<<test_vect<<" test_vect dot test_vect = "<<dotProduct<<endl;
    cout<<"magnatude of testvector is "<<test_vect.magnatude()<<endl;
	checkCondition(feq(test_vect.magnatude()*test_vect.magnatude(), dotProduct));
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
    checkCondition(gotException);
    math_matrix ident3 = ident(3);
    math_vector test_vect_duped = ident3 * test_vect;

    checkCondition(test_vect_duped == test_vect);


    math_matrix test_mat_copy(test_mat);
	test_mat.divide_row(2,5);
    test_mat.multiply_row(2,5);
	checkCondition(test_mat_copy == test_mat);
	
    test_mat.add_row(0,2);
	checkCondition(! (test_mat_copy == test_mat));
	test_mat.subtract_row(0, 2);
	checkCondition(test_mat_copy == test_mat);

    // some exceptions expected.
	checkExceptionThrown2Args(FlexibleExeption, test_mat, divide_row, 2, 0)
	checkExceptionThrown2Args(FlexibleExeption, test_mat, divide_row, test_mat.num_rows()+1, 3)
	
	//drop_row
	checkExceptionThrown1Arg(FlexibleExeption, ident3, drop_row, 10)
	math_matrix droppedRow = ident3.drop_row(0);
	checkCondition(droppedRow.num_rows() == 2);
	math_matrix droppedRowAndColumn = droppedRow.drop_collum(0);
	checkCondition(droppedRowAndColumn == ident(2));
	checkExceptionThrown1Arg(FlexibleExeption, droppedRowAndColumn, drop_collum, 2)
	
	//collum
	math_matrix ident10 = ident(10);
	checkExceptionThrown1Arg(FlexibleExeption, ident10, collum, 10)


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
