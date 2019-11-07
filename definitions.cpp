#include <iostream>
#include "definitions.h"
#include <math.h>

unsigned int Definition::autoseed(double x)
{
	return(std::rand()*x+x);
}

unsigned int Definition::MAX()
{
	return(pow(2,31)-1);
}



