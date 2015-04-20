//--
// Exception class header
//
// Gouverneur Thomas - Cuisinier Gildas
//--

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>

using namespace std;

class Exception 
{
	private:
		string _error;
	public :
        Exception();
        Exception(const string *);
	Exception(const string);
	~Exception();

	string GetErr();
};


#endif
