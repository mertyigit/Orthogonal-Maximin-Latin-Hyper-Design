#include <iostream>
#include "element.h"
#include <math.h>


int Element::element(int **A, int n, int k,int p)
{	
	ele=0;
	distan=0;
	maxscore=0;
	
	
	dist=new double[n];
	

	for(i=0; i<n; i++)	dist[i] = 0;

	for(pp1=0;pp1<n-1;pp1++)
	{
		for(pp2=pp1+1;pp2<n;pp2++)
		{
			distan = 0;
			for(pp3=0;pp3<k;pp3++)
			{
				distan += abs(A[pp3][pp1]-A[pp3][pp2]);
			}
			dist[pp1] += pow(distan,(-p));
			dist[pp2] += pow(distan,(-p));
		}
	}

	for(i=0; i<n; i++)
	{
		if(dist[i]>maxscore)
        {
			maxscore = dist[i];
			ele=i;
		}
	}

	delete [] dist;
	return ele;
}

