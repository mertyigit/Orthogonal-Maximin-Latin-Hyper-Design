#ifndef corrd_h
#define corrd_h
#include <math.h>

class Corrd
{
			
private:
	
	double cor;
	double cov;
	double var;
	

public:

	double corrd(int **A, int n,int a, int b);
	
};

#endif

