/*
 * main.cpp
 *
 *  Created on: Apr 19, 2019
 *      Author: rhtkue
 *
 *      ssh key
 *      screen
 *      make file
 */

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
#include <sys/resource.h> // vergroessert rekursionstiefe bei rekursivem programmieren
#include "mtwist.h"
#include "constants.h"
#include "functions.h"

using namespace std;  // otherwise we would always have to write "std::vector" instead of just "vector"



int main(){

	//const clock_t begin_time = clock(); // Startzeit des Programms
	//auto start = chrono::steady_clock::now();
        
	srand(time(NULL));
        
    rlimit R;                   // aendert max rekursionstiefe
    getrlimit(RLIMIT_STACK, &R);
    R.rlim_cur = R.rlim_max;
    setrlimit(RLIMIT_STACK, &R);
        
	sprintf(file1,"./Messwerte/WOLFF_Werte_L_%d_beta_%.3f_sweeps_%d_drops_%d.txt",N,beta,Measurements,EquilibriumWait); //schreibe file namen
	outputfile.open(file1,ios::out); //oeffne File
    outputfile<<"# Mag \t Suszeptibilitaet \t Korrelationslaenge \t x\n";
    initializeClusterprobability(); 
    /* initial configuration (cold start) */
	for(int i=0;i<N;i++){
		
		for(int j=0;j<N;j++){
		
			s[i][j] = 1;
		
		}
	
	}
    for(int i=0;i<Measurements;i++){
        wolffAlgorithm();
        
        measureObservables();
    }
	outputfile.close(); // schliesse File
    
    return 0;
}
