#ifndef GITTER_H
#define GITTER_H

#include <string>     // needed for strings
#include <vector>     // needed for vectors
#include <fstream>    // needed for "ifstream" and "ofstream" (file input/output)
#include <sstream>    // needed for "stringstream"
#include <iostream>   // needed for "cout" (console output)
#include <iomanip>    // needed for "scientific" and "setw" format manipulators
#include <cstdlib>    // needed for "rand" (random numbers)
#include <algorithm>  // needed for "pow" (x^y)
#include <cmath>
#include <limits>
#include <ctime>
#include "constanten.h"

double random_number(){ //random Number generator siehe constanten.h
//   double q; // generates random number between 1 and -1
//   q = (double)rand()/RAND_MAX;
//   return q;
//     return uni_real_distr(generator);
    return unif(rng);
}

void findeNachbarn(void){

	for(int i=0;i<lsqred;i++){
		oben[i]=(i-L+lsqred)%lsqred;
		unten[i]=(i+L+lsqred)%lsqred;
		links[i]=(i-1)%L+(i/L)*L; // i/L gibt integer zurueck
		rechts[i]=(i+1)%L+(i/L)*L;
	}
	links[0]=L-1;
}


void printVector(vector<int> &prinVec){
	int len=prinVec.size();
	//printf("len: %d\n",len);
	for(int i=1;i<=len;i++){
		printf("%d ",prinVec[i-1]);
		if(i%L==0) printf("\n");  //printf("\t i: %d\n",i);
	}
}

void printSpins(){
	int len=spins.size();
	for(int i=1;i<=len;i++){
		if(spins[i-1]<0) printf("- ");
		else printf("+ ");
		if(i%L==0) printf("\n");
	}
}

void coldStart(){
	for(int i=0;i<lsqred;i++){
			spins[i]=-1;	//alle spins auf -1 setzen
		}
	mag=-lsqred;
}

void hotStart(){
	mag=0; // magnetisierung auf Null setzen, falls noch ein Wert gespeichert ist
	for(int i=0;i<lsqred;i++){ // zufaellig die spins ausrichten und magnetisierung der zufaelligen Konfiguration mit berechnen
		if(random_number()<=0.5){
			spins[i]=-1;
			mag--;
		}
		else{
			spins[i]=1;
			mag++;
		}
	}

}



#endif
