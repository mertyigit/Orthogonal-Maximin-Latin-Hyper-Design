#include <iostream>
#include "column.h"
#include <math.h>
#include "corrd.h"

int Column::column(int **A, int n,int k)
{
	Corrd corrd;
	
	correlation=new double[k];
	
	col=0;
	maxcorr=0;
	
 	for(i=0;i<k;i++){
	correlation[i] = 0;
	}
	
	
	for(int p1=0;p1<k;p1++)
	{
		for(int p2=0;p2<k;p2++)
		{
			if(p2!=p1)
			{
				correlation[p1] += corrd.corrd(A,n,p1,p2);
			}
		}

		if (correlation[p1] < 0 ) correlation[p1] *= -1;

		if(correlation[p1] >= maxcorr)
		{
			maxcorr = correlation[p1];
            col=p1;
		}
	}
	delete [] correlation;

	return(col);

}

