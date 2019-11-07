#include <iostream>
#include "corrd.h"
#include <math.h>


double Corrd::corrd(int **A, int n,int a, int b)
{

	cor=0;
	cov=0;
	var=0;
	const double p2tm1 = pow(2,(-1));
	
	for(int i1=0;i1<n;i1++)
	{
 		cov += (A[a][i1]-(n+1)*p2tm1) * (A[b][i1]-(n+1)*p2tm1);
		var += (A[0][i1]-(n+1)*p2tm1) * (A[0][i1]-(n+1)*p2tm1);
	}
	cor = cov * pow(var,(-1));
	
	return(cor);
}

