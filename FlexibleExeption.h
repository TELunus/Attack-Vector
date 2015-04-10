#ifndef FLEXIBLEEXEPTIN_H
#define FLEXIBLEEXEPTIN_H

#include <exception>
#include <string>

using namespace std;
class FlexibleExeption: public exception
{
    string m_text;
    public:
    FlexibleExeption(const string & text) throw();
    virtual ~FlexibleExeption() throw() {}
    virtual const char* what() const throw();

};
#endif
