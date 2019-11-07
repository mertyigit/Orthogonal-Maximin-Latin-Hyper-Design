#include <iostream>
#include "score.h"
#include <math.h>


double Score::score(int **A, int n, int k,int p) 
{
	scoree=0;
	count=0;
	c=0;
	
    int dim=n*(n-1)/2;
	
	di=new int[dim];
	ji=new int[dim];

	for(i=0;i<dim;i++)
	{
		di[i] = 0;
		ji[i] = 1;
	}

   	for(int k1=0;k1<(n-1);k1++)
	{
		for(int k2=(k1+1);k2<n;k2++)
		{
 			di[count++] = 0;
			
			for(int k3=0;k3<k;k3++)
			{
				di[count-1] += abs(A[k3][k1]-A[k3][k2]);
			}
			for(int k4=0;k4<(count-1);k4++)
			{
				if(di[count-1]== di[k4])
				{
					ji[k4]++;
                    count--;
				}
			}
		}

	}
 	for(i=0; i<count; i++)
	{
		scoree += (ji[i])* pow(di[i],(-p));

	}

	scoree=pow(scoree,(pow(p,(-1))));

	delete [] di;
	delete [] ji;

	return(scoree);
}