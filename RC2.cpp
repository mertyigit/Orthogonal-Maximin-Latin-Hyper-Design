#include <iostream>
#include "RC2.h"
#include "RC.h"
#include <math.h>
#include "definitions.h"

int RC2::rc2(int n,int del,double seed)
{
	RC rc;
	
	rctwo= rc.rc(n-1,seed);
	
	if (rctwo >= del){
		rctwo++;
	}
	
	return(rctwo);
}