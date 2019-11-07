#include <iostream>
#include "DJ.h"
#include <math.h>


void DJ::djinformation(int **A, int n, int k, int* Mminf)
{
	scoree=0;
	count=0;
	c=0;
	
	const int dim= (int)(n*(n-1)*0.5);
	
    d=new int[dim];
	j=new int[dim];
	
	for(int i=0;i<dim;i++)
	{
		d[i] = 0;
		j[i] = 1;
	}


   	for(int k1=0;k1<(n-1);k1++)
	{
		for(int k2=(k1+1);k2<n;k2++)
		{
 			d[count]=0;
			count++;

			for(int k3=0;k3<k;k3++)
			{
				d[count-1] += abs(*(*(A+k3)+k1)-*(*(A+k3)+k2));
			}
			for(int k4=0;k4<(count-1);k4++)
			{
				if(d[count-1]==d[k4])
				{
					j[k4]++;
                    count--;
				}
			}
		}
	}

	int Mmd=100000;
	int Mmj=0;

	for(int k5=0;k5<count;k5++)
	{
		if(Mmd>d[k5])
		{
			Mmd= d[k5];
			Mmj= j[k5];
		}
	}

	Mminf[0] = Mmd;
	Mminf[1] = Mmj;

	delete [] d;
	delete [] j;

}