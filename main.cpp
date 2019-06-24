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
#include "gitter.h"
#include "constanten.h"
#include "methoden.h"

using namespace std;  // otherwise we would always have to write "std::vector" instead of just "vector"



int main(){

	//const clock_t begin_time = clock(); // Startzeit des Programms
	//auto start = chrono::steady_clock::now();
        
	srand(time(NULL));
        
        rlimit R;                   // aendert max rekursionstiefe
        getrlimit(RLIMIT_STACK, &R);
        R.rlim_cur = R.rlim_max;
        setrlimit(RLIMIT_STACK, &R);
        
        int number_of_configurations = leseStartfile(0,startfilename) -1; // berechne Anzahl an configurationen
        cout<<"Anzahl an Konfigurationen : "<<number_of_configurations<<"\n\n";
    for(int i=1;i<=number_of_configurations;i++){
        cout<<"Lade Konfiguration "<<i<<" / "<<number_of_configurations<<" : ";
	initialisiereKonstanten(i);
        cout<<"L:"<<L<<" / beta:"<<beta<<" / sweeps:"<<sweeps<<"\n";
	sprintf(file1,"./Messdaten/WOLFF_Werte_L_%d_beta_%.3f_sweeps_%d_drops_%d.txt",L,beta,sweeps,drop); //schreibe file namen

	outputfile.open(file1,ios::out); //oeffne File
        outputfile<<"# Mag \t Suszeptibilitaet \t Korrelationslaenge \t x\n";
 	hotStart(); //initialisiere System
	findeNachbarn();// findet Indizes der benachbarten Spins
	cout<<"clusterWahrscheinlichkeit: "<<clusterWahrscheinlichkeit<<"\n";
        
//         printSpins();

// 	//METROPOLIS-ALGORITHMUS
// 	cout<<"thermlisieren ... ";
// 	thermalisierenMETRO(drop); //thermalisieren System mit drop flips
//         
//         cout<<"done\n";
// //         printSpins();
//         cout<<"starte Metropolisalgorithmus ... ";
//         
// 	for(int j=0;j<sweeps;j++){ //eigentlicher Metropolisalgorithmus
//             metropolis();
// 	}
// 	
// 	cout<<"done\n";
//         printSpins();
// 	//WOLFF-ALGORITHMUS
//         cout<<"thermalisieren ... ";
// 	thermalisierenWOLFF_RE(drop); //thermalisieren System mit drop flips
//         cout<<"done\n";
//         cout<<"starte Wolffalgorithmus ... \n";
// 	wolffAlgorithmus_RE();
        printSpins();
        wolff_IT();
        printSpins();
//         cout<<sweeps<<" / "<<sum_counter<<"\n";
//         cout<<"mittelSuszeptibilitaet / L:\t"<<(double) beta*suszeptibilitaet/sweeps<<" / "<<L<<"\n";
// 	cout<<"done\n\n";
//         
//         
// 	//printf("Dauer: %f",float( clock () - begin_time )/  std::CLOCKS_PER_SEC);
        
	outputfile.close(); // schliesse File
    }
        return 0;
}
