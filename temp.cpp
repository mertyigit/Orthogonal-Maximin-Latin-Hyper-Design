#include <iostream>
#include "temp.h"
#include <math.h>


double Temp::t0(int n, int k, int p)
{
	dbar = (n+1)*k*pow(3,(-1));
	c = 0.5;
	p0 = 0.99;
	pf = 0.01;
	t1 = (pow(dbar,(-p))*n*(n-1))*pow(4*c*(p-1),(-1));
	t2 = pow((1-c),(1-p));
	t3 = pow((1+c),(1-p));
	phi0 = pow((t1*(t2-t3)),(pow(p,(-1))));
	delt0 = pow((pow(phi0,p)-pow((1-c)*dbar,(-p))+pow((1-c)*dbar-1,(-p))-pow((1+c)*dbar,(-p))+pow((1+c)*dbar+1,(-p))),pow(p,(-1)));
	t_zero = -delt0*pow((log(p0)),(-1));

	return(t_zero);
}