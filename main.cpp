#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>


#include "element.h"
#include "column.h"
#include "corrd.h"
#include "LB.h"
#include "UB.h"
#include "mcorr.h"
#include "DJ.h"
#include "score.h"
#include "definitions.h"
#include "RC.h"
#include "RC2.h"
#include "runif.h"
#include "LHD.h"
#include "temp.h"

////////////////////////////////////////////////////
////////////// CLASS DECLERATIONS /////////////////
//////////////////////////////////////////////////

Element element;
Column column;
Corrd corrd;
LB lb;
UB ub;
Mcorr mcorr;
DJ dj;
Score score;
Definition definition;
RC rc;
RC2 rc2;
Runif runif;
LHD LHD;
Temp temp_0;

int main(int argc, char *argv[])
{
  	srand(time(0));
 	std:: ofstream out;
 	out.open("parameters");
	double seed=rand();
	
  	const int k=std::atoi(argv[1]);
	std::cout << "k: "<< k << std::endl;
	
	const int n=std::atoi(argv[2]);
	std::cout << "n: "<< n << std::endl;
	
	int nsearch=2;
	
	int p=std::atoi(argv[3]);
	std::cout << "p: "<< p << std::endl;
	
	double tfac=0.95;
	const double eps=0.0000001;
	
	int nterp=std::atoi(argv[4]);
	std::cout << "nterp: "<< nterp << std::endl;
	
//////////////////////////////////////////// VARIABLE INITIALIZATIONS ////////////////////////////////////////	
	
	double t0;
	double bestyet=100000;
	double crit;
	double cor;
	double newcrit;
	double newcritbest;
	double critbest;
  	double corbest;
	double nbestyet=0;
	int itotal;
	double temp;

	int **xbest;
 	int **xtry;
	int **x;

	int *Mminf;
	Mminf=new int[2];

	int i;


//////////////////////////////////////// MATRIX INITIALIZATIONS //////////////////////////////////////////////
	xtry	=new int*[k];
  	xbest	=new int*[k];
	x=new int*[k];
	for(i=0;i<k;i++)
	{
		xbest[i] = new int[n];
		xtry[i] = new int[n];
		x[i] = new int[n];
	}

///////////////////////////////// STARTING TEMPERATURE CALCULATION ///////////////////////////////////////////

	t0=temp_0.t0(n, k, p);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	std::cout<<"start"<<std::endl;
	
	
////////////////////////////////////////// START OF LOOP ////////////////////////////////////////////////////
	
	for(int loop = 0;loop < 5;loop++)
	{
		auto start = std::chrono::high_resolution_clock::now();
		nterp = nterp + 100;
		out<< "nterp=" << nterp << "\n";
		out<< "t0=" << t0 << "\n";

///////////////////////////// CREATING RANDOM LATIN HYPER DESIGN MATRIX /////////////////////////////////////

		x=LHD.lhd(n,k,seed);
		
////////////////////////////////////// START OF SEARCH LOOP ////////////////////////////////////////////////
		
		for(int isearch=1;isearch<nsearch;isearch++)
		{		
			seed=std::rand();
			
////////////////////////////////// BEST DESIGN INITIALIZATION //////////////////////////////////////////////
		
			for(int n2=0;n2<k;n2++)
			{
				for(int n1=0;n1<n;n1++)
				{
				 *(*(xbest+n2)+n1)=*(*(x+n2)+n1);
				 *(*(xtry+n2)+n1)=*(*(x+n2)+n1);
				}
			}

			crit=score.score(x,n,k,p);
			cor=mcorr.mcorr(x,n,k);
			critbest=crit;
			corbest=cor;
			newcritbest=pow(corbest,2)+(critbest-lb.lb(n,k,p))*pow((ub.ub(n,k,p)-lb.lb(n,k,p)),(-1));
			
////////////////////////////// TEMPERATURE AND COUNT INITIZALIZATION ///////////////////////////////////////
			
			temp=t0;
			itotal=0;
			int ichange=1;
			
/////////////////////////////////// VARIABLE TEMPERATURE LOOP //////////////////////////////////////////////
			
     		while(ichange==1)
			{
				ichange=0;
				
////////////////////////////////// CONSTANT TEMPERATURE LOOP ///////////////////////////////////////////////
				
				int ipert=1;
				while (ipert<nterp)
				{
					itotal=itotal+1;
					
/////////////////////////////// SWITCH TO BE TRIED IS ELEMENTS /////////////////////////////////////////////
////////////////////////// INTERCHANGE OF TWO COMPONENT IN SAME COLUMN /////////////////////////////////////
					
					 int ind;
					 int tran1;
					 int tran2;
					 seed=rand();
					 ind=column.column(x,n,k); ind=ind-1;
					 seed=rand();
					 tran1 = element.element(x, n, k, p);
					 seed=rand();
					 tran2=rc2.rc2(n,tran1,seed);
					 
////////////////////////////////////////////// X TO XTRY ///////////////////////////////////////////////////
					 
 					 *(*(xtry+ind+1)+tran2)=*(*(x+ind+1)+tran1);
				     *(*(xtry+ind+1)+tran1)=*(*(x+ind+1)+tran2);
					 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
					 
					 double  crittry=score.score(xtry,n,k,p);
					 double  cortry=mcorr.mcorr(xtry,n,k);
					 double  newcrittry=pow(cortry,2)+(crittry-lb.lb(n,k,p))*pow((ub.ub(n,k,p)-lb.lb(n,k,p)),(-1));

//////////////////////////////////// COMPARE IF XTRY OR XBEST IS BEST ////////////////////////////////////////
					 
					if(newcrittry<newcritbest)
					{
						
/////////////////////// IF YES: REPLACE X, XBEST BY XTRY; SET ITERP=1 ; ICHANGE=1 ////////////////////////////
						ichange=1;
						for(int nn2=0;nn2<k;nn2++)
						{
						   for(int nn1=0;nn1<n;nn1++)
						   {
							  *(*(xbest+nn2)+nn1)=*(*(xtry+nn2)+nn1);
						   }
						}
						 *(*(x+ind+1)+tran1)=*(*(xtry+ind+1)+tran1);
						 *(*(x+ind+1)+tran2)=*(*(xtry+ind+1)+tran2);
						critbest=crittry;
						corbest=cortry;
						newcritbest=newcrittry;
						ipert=1;
						crit=crittry;
						cor=cortry;
						newcrit=newcrittry;

					}
					else
					{
						
//////////////////// IF NO: INCREASE IPERT BY 1. IS XTRY AS GOOD AS OR BETTER THAN X? //////////////////////
						
						ipert=ipert+1;
						//if(crittry<crit)
						if(newcrittry<newcrit)
						{
							
////////////////////////////// IF XTRY IS BETTER THAN X; REPLACE X BY XTRY ////////////////////////////////
							
 						 *(*(x+ind+1)+tran1)=*(*(xtry+ind+1)+tran1);
						 *(*(x+ind+1)+tran2)=*(*(xtry+ind+1)+tran2);
						 ichange=1;
						 crit=crittry;
						 cor=cortry;
						 newcrit=newcrittry;
						 
///////////////////////////////////////////////////////////////////////////////////////////////////////////
					}
					else
					{
///////////////////////////////////// IF XTRY IS WORSE THAN X//////////////////////////////////////////////
						
					    double delta1=crittry-crit;
						double delta2=cortry-cor;
						double range=ub.ub(n,k,p)-lb.lb(n,k,p);
					//    double prob=exp(-delta1*pow(temp,(-1)));
			        	double prob=exp(-delta1*pow(temp,(-1))-delta2*range*pow(temp,(-1)));
 					    seed=seed+isearch+ipert;
					    double q=runif.runif(seed);
					     if(prob>=q)
						 {///// replce x by xtry by prob///////////
 				           	 *(*(x+ind+1)+tran1)=*(*(xtry+ind+1)+tran1);
				             *(*(x+ind+1)+tran2)=*(*(xtry+ind+1)+tran2);
							 ichange=1;
							 crit=crittry;
							 cor=cortry;
							 newcrit=newcrittry;
						 }
						 
//////////////////////////////////////////////////////////////////////////////////////////////////////////// 
                         else
						 {		 
//////////////////////////////// RESET XTRY TO X FOR THE NEXT PERTURBATION /////////////////////////////////
							 
 				           	 *(*(xtry+ind+1)+tran1)=*(*(x+ind+1)+tran1);
				             *(*(xtry+ind+1)+tran2)=*(*(x+ind+1)+tran2);
						 }
						 
////////////////////////////////////////////////////////////////////////////////////////////////////////////		 
					}
				}
			}	
///////////////////////////////////// END OF CONSTANT TEMPERATURE LOOP /////////////////////////////////////
			
			temp=temp*tfac;
		}
		
///////////////////////////////////// END OF VARIABLE TEMPERATURE LOOP /////////////////////////////////////
////////////////////////////////////////// RESULT OF THIS SEARCH ///////////////////////////////////////////
		
        if(newcritbest<(bestyet+eps))
		{
			nbestyet=nbestyet+1;
		}
    	if(newcritbest<(bestyet-eps))
		{
			bestyet=newcritbest;
			nbestyet=1;
		}

		for(int ii=0;ii<n;ii++)
		{
			for(int jj=0;jj<k;jj++)
			{
				out<<*(*(xbest+jj)+ii)<<"  ";
			}
			out<<"\n";
		}
	double combine=pow(mcorr.mcorr(xbest,n,k),2)+(score.score(xbest,n,k,p)-lb.lb(n,k,p))*pow((ub.ub(n,k,p)-lb.lb(n,k,p)),(-1));

	dj.djinformation(xbest,n, k, Mminf);
	out<<"d="<<*(Mminf+0)<<",j="<<*(Mminf+1)<<"\n";
	out<<"score="<<newcritbest<<"\n";
	out<<"isearch="<<isearch<<"\n";
	out<<"Number of design examed="<<itotal<<"\n";
	out<<"phi_p="<<score.score(xbest,n,k,p)<<"\n";
	out<<"correlation="<<mcorr.mcorr(xbest,n,k)<<"\n";

/////////////////////////////////////////////// END OF SEARCH LOOP /////////////////////////////////////////
	
   }
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Elapsed time: " << elapsed.count() << " s\n";
}

//////////////////////////////////////////////// CLEAR THE MATRISES ////////////////////////////////////////
	for(i=0; i<k; i++)
	{
		delete [] xbest[i];
		delete [] xtry[i];
		delete [] x[i];
	}

	delete []xbest;
	delete []xtry;
	delete []x;
    delete []Mminf;
}















