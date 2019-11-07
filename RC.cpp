#include <iostream>
#include "RC.h"
#include <math.h>
#include "definitions.h"

int RC::rc(int n,double seed ) // choose randomly from 0 to (n-1)
{

   Definition definition;

   u = (double) (std::rand()*definition.autoseed(seed)%definition.MAX())/definition.MAX();   
   r=(int)(n*u);
   return(r);
}