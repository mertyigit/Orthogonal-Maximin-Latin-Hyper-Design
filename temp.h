#ifndef temp_h
#define temp_h

class Temp
{
		
private:
	
	double dbar;
	double c;
	double p0;
	double pf;
	double t1;
	double t2;
	double t3;
	double phi0;
	double delt0;
	double t_zero;
	
public:

	double t0(int n, int k, int p);
	
};

#endif

