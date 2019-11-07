#include <iostream>
#include "mcorr.h"
#include <math.h>
#include "corrd.h"


double Mcorr::mcorr(int **A, int n,int k)
{
	Corrd corrd;

	mcor=0;
	
 	for(int j1=1;j1<k;j1++)
	{
		for(int j2=0;j2<j1;j2++)
		{
			mcor += pow(corrd.corrd(A,n,j1,j2),2);
		}
	}

	mcor = 2 * mcor / (double)(k*(k-1));
	mcor = pow(mcor,(0.5));
	return(mcor);
}

