#include "FlexibleExeption.h"
FlexibleExeption::FlexibleExeption(const string & text) throw()
: exception(), m_text(text)
{
}

const char* FlexibleExeption::what() const throw()
{
    //std::cout << m_text;
    return m_text.c_str();
}
