/* headerfile functionsising2d.h */
/* contains functions for the 2d ising simulation */
/* initializeBoltzmannLookup: creates lookup table for the boltzmann factors */
// void initializeBoltzmannLookup(void){
	
// 	boltzmann[0][4] = 1;
// 	boltzmann[2][4] = 1;
// 	boltzmann[0][0] = exp(-8*J*beta);
// 	boltzmann[0][2] = exp(-4*J*beta);
// 	boltzmann[0][6] = 1;
// 	boltzmann[0][8] = 1;
// 	boltzmann[2][0] = 1;
// 	boltzmann[2][2] = 1;
// 	boltzmann[2][6] = boltzmann[0][2];
// 	boltzmann[2][8] = boltzmann[0][0];

// }

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

using namespace std;

double random_number() {
  double q; // generates random number between 1 and -1
  q = (double)rand()/RAND_MAX;
  return q;
}

/* initializeClusterprobability: calculate probability to add spin to the cluster for the wolff alogrithm */
void initializeClusterprobability(void){
	
	clusterprobability = 1-exp(-2*beta*J);
		
}

/* mcsweep: performes the monte carlo step for a given temperature*/
// void mcsweep(void){
	
// 	int p, q, r;
// 	for(p = 0; p < BetweenMeasurements; p++){
		
// 		for(q = 0; q < N; q++){
			
// 			for(r = 0; r < N; r++){
// 				/* periodic boundary conditions */
// 				/* gets the interaction with neighbours through counting them */
// 				nn = s[q][(r+1)%N] + s[q][(r+N-1)%N] + s[(q+1)%N][r] + s[(q+N-1)%N][r] + 4;
// 				si = s[q][r] + 1;
// 				/* accept new configuration if it is energetically favourable */
// 				if(boltzmann[si][nn] == 1){
				
// 					s[q][r] = -s[q][r];
					
// 				}
// 				/* accept even if energetically unfavourable with probability given by boltzmann factors */
// 				else if(genrand_real2() < boltzmann[si][nn]){
					
// 					s[q][r] = -s[q][r];
					
// 				}
				
// 			}
			
// 		}
		
// 	}

// }

/* function declaration for tryAdd() */
void tryAdd(int i, int j, short spin);

/* growCluster: builds wolff cluster */
void growCluster(int i, int j, short spin){

    /* flip the spin belonging to the cluster */
    s[i][j] = -s[i][j];
    cluster[i][j] = 1;
    clustersize++;
    
    /* get neighbouring indices with periodic boundary conditions */
    int i_prev = i == 0 ? N-1 : i-1;
    int i_next = i == N-1 ? 0 : i+1;
    int j_prev = j == 0 ? N-1 : j-1;
    int j_next = j == N-1 ? 0 : j+1;
    
    /* tries adding the neighbouring spins the the cluster */
    tryAdd(i_prev, j, spin);
    tryAdd(i_next, j, spin);
    tryAdd(i, j_prev, spin);
    tryAdd(i, j_next, spin);

}

/* tryAdd: adds appropriate Spins to the cluster */
void tryAdd(int i, int j, short spin){

    /* checks if the spinorientation matches the cluster */
    if(s[i][j] == spin){
    
        /* only adds spin with wanted probability */
        // if(genrand_real2() < clusterprobability){
        if(random_number() < clusterprobability){
        
            /* adds spin to the cluster */
            growCluster(i, j, spin);
        
        }
    
    }

}

void resetCluster(void){
    int i, j;
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            cluster[i][j] = 0;
        }
    }
}

/* wolffAlgorithm: performes the wolff algorithm, return the clustersize */
void wolffAlgorithm(){
    int i;
    
    for(i = 0; i < BetweenMeasurements; i++){
        /* set clustersize to 0 */
        int size = 0;
        while(size < N*N){
            
            clustersize = 0;
            resetCluster();
            /* choose random spin and grow the cluster */
    //         cout<<i;
            // int i = genrand_real2() * N;
    //         // int j = genrand_real2() * N;
            int i = random_number() * N;
            int j = random_number() * N;
            
            growCluster(i, j, s[i][j]);
            size=clustersize;

        }
        
    }

}

/* moment: calculates the current magnetization per site of the lattice */
double mag(void){
	
	int i, j, sum = 0;
	/* loop over entire spin lattice */
	for(i = 0; i < N; i++){
		
		for(j = 0; j < N; j++){
			
			/* calculate the moment */
			sum += s[i][j];
		
		}
		
	}
	/* return the magnetization per site */
    cout<<(double)sum/(N*N)<<"\n";
	return (double)sum/(N*N);

}

/* ene: calculates the internal energy per site of the lattice */
double ene(void){
	
	int i, j, sum = 0;
	/* loop over entire spin lattice */
	for(i = 0; i < N; i++){
		
		for(j = 0; j < N; j++){
			
			/* only calculate to the right and upwards to prevent double counting */
			sum += -J*s[i][j] * (s[i][(j+1)%N] + s[(i+1)%N][j]);
			
			
		}
		
	}
	/* return the internal energy per site */
	return (double)sum/(N*N);
	
}

/* ssreset: resets the spin-spin correlation variable */
void ssreset(void){

    int j;
    for(j = 0; j < N/2+1; j++){
    
        sscorr[j] = 0;
    
    }

}

/* improved estimator from janke paper */
void improvedestimator(void){

    double k = 2*PI/N;
    double co = 0;
    double si = 0;
	clustersize = 0;
    int i, j;
    for(i = 0; i < N; i++){
    
        for(j = 0; j < N; j++){
        
            if(cluster[i][j] == 1){
			   clustersize++;
               co += cos(k*i + k*j);
               si += sin(k*i + k*j); 
            
            }
        
        }
    
    }
	
    g_k = (double)(co*co + si*si) / clustersize / (N*N);
    g_0 = (double)clustersize / (N*N);

}

/* spinspincorr: measures spin-spin correlation */
// Notfallplan
void spinspincorr(void){

    ssreset();
    int i, j;
    for(i = 0; i < N; i++){
    
        for(j = 0; j < N/2+1; j++){
        
            sscorr[j] += (double) s[i][i] * ( s[i][(i+j)%N] + s[(i+j)%N][i] + s[i][(N+i-j)%N] + s[(N+i-j)%N][i]) / (4 * N);
        
        }
    
    }

}


// void print_to_file(void){
	
// 	int i;
// 	fprintf(fp,"%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n",temperature,magnet1,magnet2,magnet4,energy1,energy2, g_0,g_k);
// 	/*for(i = 0; i < N/2+1; i++){
// 		//NOTFALL
//         fprintf(fp1,"%f\t%d\t%f\n",temperature,i,sscorr[i]);
    
//     }*/

// }

/* measureObservables: measures the observables for the current state of the lattice */
void measureObservables(void){

    //spinspincorr(); NOTFALL
    // improvedestimator();
    magnet1 = mag();
    cout<<magnet1<<"\n";
    // magnet2 = magnet1 * magnet1;
    // magnet4 = magnet2 * magnet2;
    // energy1 = ene();
    // energy2 = energy1 * energy1;

}
/* simulationDriver: handles the simulation process for the different modes */
/* mode 1: metropolis algorithm */
/* mode 2: wolff algorithm */
// void simulationDriver(int mode){
// 	printf("wow");
// 	int i;
// 	beta = 1/temperature;						/* calculate the inverse temperature */
// 	initializeBoltzmannLookup();                /* calculate the transitionprobabilities */
//     initializeClusterprobability();              
// 	for(i = 0; i < EquilibriumWait; i++){             /* dont measure until equilibrium */

//         if(mode == 1) mcsweep();
//         else if(mode == 2) wolffAlgorithm();  
        
//     }
// 	magnet1 = 0; magnet2 = 0; magnet4 = 0;		/* saves the magnetization, magnetization**2 and magnetization**4*/
// 	energy1 = 0; energy2 = 0;					/* saves the internal energy and energy**2 */

// 	/* perform desired amount of measurements for the given temperature */
// 	for(i = 0; i < Measurements; i++){
//         /* selects the wanted mode for the calculations */
// 		if(mode == 1){

// 			mcsweep();
			
// 		}
// 		else if(mode == 2){
			
// 			wolffAlgorithm();
			
// 		}
// 	    /* measure the observables for the current state */
// 	    measureObservables();
// 	    /* save the observables into the file */
// 		// print_to_file();
// 		// Progress indicator
// 		printf("%d\n",i);
// 	}
	
// }
