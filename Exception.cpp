//--
// Exception class definition
//
// Gouverneur Thomas - Cuisinier Gildas
//--

#include "Exception.h"

using namespace std;

Exception::Exception() : _error("Unknown error !")
{
}

Exception::Exception(const string* msg) : _error(*msg)
{
}
Exception::Exception(const string msg) : _error(msg)
{
}

Exception::~Exception()
{
}

string Exception::GetErr() 
{
	return this->_error;
}
