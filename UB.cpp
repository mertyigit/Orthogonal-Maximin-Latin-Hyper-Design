#include <iostream>
#include "UB.h"
#include <math.h>


double UB::ub(int n, int k,int p)
{
	ube=0;
	
	for(int i=1;i<(n-1);i++)
	{
		ube += (n-i)* pow((i*k),(-p));
	}
	ube = pow(ube,(pow(p,(-1))));
	
	return(ube);
}