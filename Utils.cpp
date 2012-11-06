/*
 *  Utils.cpp
 *  AV
 *
 *  Created by John Klippenstein on 12-10-31.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Utils.h"
#include <cmath>

bool feq( double lhs, double rhs, double tolerance)
{
	return fabs(lhs - rhs) < tolerance || fabs(rhs - lhs) < tolerance;
}