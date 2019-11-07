#include <iostream>
#include "runif.h"
#include <math.h>
#include "definitions.h"

double Runif::runif(double seed)
{
   Definition definition;
   runiff= (double) (std::rand()*definition.autoseed(seed)%definition.MAX())/definition.MAX();
   return(runiff);
}