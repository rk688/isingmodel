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
#include "gitter.h"
#include "constanten.h"
#include "methoden.h"

using namespace std;  // otherwise we would always have to write "std::vector" instead of just "vector"



int main(){

	//const clock_t begin_time = clock(); // Startzeit des Programms
	//auto start = chrono::steady_clock::now();

	srand(time(NULL));
	//printf("%f",random_number());
	//findeNachbarn();

	initialisiereKonstanten(3);
	sprintf(file1,"./Messdaten/Magnetisierungswerte.txt"); //schreibe file namen
	ofstream out_mag(file1,ios::out); //oeffne File
 	coldStart(); //initialisiere System
	findeNachbarn();// findet Indizes der benachbarten Spins
	cout<<"clusterWahrscheinlichkeit: "<<clusterWahrscheinlichkeit<<" // beta: "<<beta<<"\n";
        
        printSpins();

	//METROPOLIS-ALGORITHMUS
	/*
	for(int i=0;i<drop;i++){
			metropolis(); // ein Metropolis-Sweep
		}
	for(int i=0;i<sweeps-drop;i++){
		metropolis(); // ein Metropolis-Sweep
		out_mag<<mag<<"\n"; // schreibe Magnetisierungswert und File
		mittelMag=mittelMag+mag;
	}
	*/

// 	printSpins();
	cout<<"\n\n\n";
	//WOLFF-ALGORITHMUS
	wolffSweep();
// 	printSpins();
	printf("mag: %d\n\n\n\n",mag);
	cout<<"\n\n\n";
	//printf("Mittel Magnetisierung: %f\nbeta: %f \nfertig",mittelMag/((sweeps-drop)*lsqred),1/(k*T));

	//printf("Dauer: %f",float( clock () - begin_time )/  std::CLOCKS_PER_SEC);
        
	out_mag.close(); // schliesse File
        return 0;
}
