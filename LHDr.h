#ifndef LHDr_h
#define LHDr_h

class LHDr
{
		
private:
	
	int te;
	double **lhdv;
	double *r;
	
	
public:

	double **lhd(int n, int k, double seed);
	
};

#endif

