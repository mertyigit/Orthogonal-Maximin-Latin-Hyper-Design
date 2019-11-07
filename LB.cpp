#include <iostream>
#include "LB.h"
#include <math.h>

double LB::lb(int n,int k,int p)
{
	lbe=0;
	lbe=3*pow((n+1)*k,(-1))*pow(n*(n-1)*pow(2,(-1)),(pow(p,(-1))));
	
	return(lbe);
}
