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
#include <random>
#include <chrono>
#include "gitter.h"
#include "constanten.h"
#include "methoden.h"

using namespace std;  // otherwise we would always have to write "std::vector" instead of just "vector"



int main(){
    
    // initialize the generator with time-dependent seed
    uint64_t timeSeed = chrono::high_resolution_clock::now().time_since_epoch().count();
    seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
    rng.seed(ss);
    //Fuer srand Methode
//     srand(time(NULL));

	const clock_t begin_time = clock(); // Startzeit des Programms
// 	auto start = chrono::steady_clock::now();
        
        rlimit R;                   // aendert max rekursionstiefe
        getrlimit(RLIMIT_STACK, &R);
        R.rlim_cur = R.rlim_max;
        setrlimit(RLIMIT_STACK, &R);
        
        int number_of_configurations = leseStartfile(0,startfilename) -1; // berechne Anzahl an configurationen
        cout<<"Anzahl an Konfigurationen : "<<number_of_configurations<<"\n\n";
    for(int i=1;i<=number_of_configurations;i++){
        //gibt Startuhrzeit jeder konfiguration
        auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
        const clock_t start_time = clock();
        cout << ctime(&timenow);
        
        cout<<"Lade Konfiguration "<<i<<" / "<<number_of_configurations<<" : ";
	initialisiereKonstanten(i);
        cout<<"L:"<<L<<" / beta:"<<beta<<" / sweeps:"<<sweeps<<"\n";
	sprintf(file1,"./Messdaten/WOLFF_Werte_L_%d_beta_%.5f_sweeps_%d_drops_%d.txt",L,beta,sweeps,drop); //schreibe file namen

	outputfile.open(file1,ios::out); //oeffne File
        outputfile<<"# Messwerte zu "<<L<<"x"<<L<<" und beta: "<<beta<<" mit "<<sweeps<<" Messwerten"<<endl;
        outputfile<<"# Norm. Magenetisierung || Mag^2 || Mag^4 || Clustergroesse G(0) || G(k)\n";
 	hotStart(); //initialisiere System
	findeNachbarn();// findet Indizes der benachbarten Spins
	cout<<"clusterWahrscheinlichkeit: "<<clusterWahrscheinlichkeit<<"\n";

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
        
// 	//WOLFF-ALGORITHMUS
        cout<<"thermalisieren ... ";
	thermalisierenWOLFF_RE(); //thermalisieren System mit drop flips
        cout<<"done\n";
        cout<<"starte Wolffalgorithmus ... ";
	wolffAlgorithmus_RE();
	cout<<"done\n";
        
        //DURCHLAUFZEITEN
        double totaleDauer=(float) (clock()-begin_time)/CLOCKS_PER_SEC;
        double startDauer=(float) (clock()-start_time)/CLOCKS_PER_SEC;
	cout<<"gesamte Dauer: \t\t"<<totaleDauer<<" sec"<<" / "<<totaleDauer/60<<" min"<<endl;
        cout<<"nur fuer Konfiguration: "<<startDauer<<" sec"<<" / "<<startDauer/60<<" min"<<endl<<endl<<endl;
        
	outputfile.close(); // schliesse File
    }
        return 0;
}
