#ifndef column_h
#define column_h

class Column
{
		
private:
	
	int col;
	int i;
	double maxcorr;
	double *correlation;
	
public:

	int column(int **A, int n,int k);
	
};
	
#endif

