#include <iostream>
#include "LHDr.h"
#include "RC.h"
#include <math.h>
#include "definitions.h"

double** LHDr::lhd(int n, int k, double seed)
{	
	
	RC rc;
	Definition def;
	
	//std::cout << (double) (std::rand()*def.autoseed(seed)%def.MAX())/def.MAX() << std::endl;
	
	r=new double [n];
    lhdv=new double*[k];
	
	for(int iii=0;iii<k;iii++)
	{
		lhdv[iii]=new double[n];
	}
     
	for(int j2=0;j2<n;j2++)  
	{
		*(*(lhdv+0)+j2)=(j2+(double) (std::rand()*def.autoseed(seed)%def.MAX())/def.MAX())/(double)n;
	}
	
	for(int j1=0;j1<(k-1);j1++)
	{
	   for(int cc=0;cc<n;cc++)
	   {
		*(r+cc)=(cc+(double) (std::rand()*def.autoseed(seed)%def.MAX())/def.MAX())/(double)n;
	   }
	   for(int c=0;c<n;c++)
	   {
			seed=seed+j1*c;
			seed=seed+10;
			te=rc.rc(n-c,seed);
			*(*(lhdv+j1+1)+c)=*(r+te);
			
		    for(int c1=0;c1<(n-c);c1++)
			{
			    if(c1>=te)
				{
				*(r+c1)=*(r+c1+1);
				}
			}
	   }
	}
   return(lhdv);
   
   for(int iiii=0;iiii<k;iiii++)
   {
	delete [] lhdv[iiii];
   }
   
   delete [] lhdv;
   delete [] r;
   
}