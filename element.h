#ifndef element_h
#define element_h

class Element
{
			
private:
	
	int ele;
	double distan;
	double maxscore;	
	double *dist;	
		
	int pp1, pp2, pp3;
	int i;
	
	
public:

	int element(int **A, int n, int k,int p);
	
};


#endif

