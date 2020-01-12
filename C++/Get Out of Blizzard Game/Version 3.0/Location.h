//
//  Location.h
//

#ifndef LOCATION_H
#define LOCATION_H

#include <iostream>



//
//  Location
//
//  A class to represent a location in the world.  A Location is
//    like a node index, except that it isn't necessarily an
//    integer.  A Location contains sufficient information to
//    uniquely identify a node.
//
class Location
{
public:
//
//  Default Constructor
//
//  Purpose: To create an Location representing a default node.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: A new Location is created that represents node
//               (0, 0).
//
	Location ();

//
//  Initializing Constructor
//
//  Purpose: To create an Location representing the specified
//           node.
//  Parameter(s):
//    <1> row1:    The node row
//    <1> column1: The node column
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: A new Location is created that represents node
//               (row1, column1).
//
	Location (unsigned int row1, unsigned int column1);

//
//  Equality Test Operator
//
//  Purpose: To determine if two Locations represent the same
//           node.
//  Parameter(s):
//    <1> other: The other Location
//  Precondition(s): N/A
//  Returns: Whether this Location and oother represent the same
//           node in the world.
//  Side Effect: N/A
//
	bool operator== (const Location& other) const;

public:
	unsigned int row;
	unsigned int column;
};

//
//  Stream Insertion Operator
//
//  Purpose: To print the specified Location to the specified
//           output stream.
//  Parameter(s):
//    <1> out: A reference to the output stream
//    <2> location: The Location
//  Precondition(s): N/A
//  Returns: A reference to out.
//  Side Effect: Location location is printed to output stream
//               out.
//
std::ostream& operator<< (std::ostream& out,
                          const Location& location);



#endif
