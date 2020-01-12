//
//  Location.cpp
//

#include <iostream>

#include "Location.h"

using namespace std;



Location :: Location ()
		: row(0),
		  column(0)
{
}

Location :: Location (unsigned int row1, unsigned int column1)
		: row   (row1),
		  column(column1)
{
}



bool Location :: operator== (const Location& other) const
{
	return row    == other.row    &&
	       column == other.column;
}



ostream& operator<< (ostream& out,
                     const Location& location)
{
	cout << "(row = "    << location.row
	     << ", column =" << location.column << ")";
	return out;
}
