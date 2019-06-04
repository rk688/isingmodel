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
    for(int i=1;i<=1;i++){
	initialisiereKonstanten(i);
	sprintf(file1,"./Messdaten/METRO_Werte_L_%d_beta_%.3f.txt",L,beta); //schreibe file namen
	outputfile.open(file1,ios::out); //oeffne File
 	hotStart(); //initialisiere System
	findeNachbarn();// findet Indizes der benachbarten Spins
	cout<<"clusterWahrscheinlichkeit: "<<clusterWahrscheinlichkeit<<" // beta: "<<beta<<"\n";
        
        printSpins();

	//METROPOLIS-ALGORITHMUS
	
	for(int i=0;i<drop;i++){
			metropolis(); // ein Metropolis-Sweep
		}
        
        cout<<"\n\n";
//         printSpins();
//         cout<<"\n\n";
// 	for(int j=0;j<2000;j++){
// 		/*metropolis();*/// ein Metropolis-Sweep
//                 for(int i=0;i<lsqred;i++){// for-schleife um einen Sweep zu bekommen, da zufaellige Spinauswahl genutzt wird
//                     int q=random_number()*lsqred; //zufaelliger Spin wird ausgesucht
//                     double deltaE=2*J*spins[q]*(spins[links[q]]+spins[rechts[q]]+spins[unten[q]]+spins[oben[q]]); // Eneu-Ealt
//                     double boltz=exp(-deltaE*beta);
//                     double w=fmin(1,boltz);
//                     if(random_number()<=w){
// 			spins[q]=-spins[q]; // wenn neue zufaellige Nummer kleiner ist als Wahrscheinlickeit w, wird der Spin an der Stelle q geflippt
// 			//Messgroessenupdates
// 			mag=mag+2*spins[q]; // update die Magnetisierung nach jedem Spinflip
// 			
//                     } 
//                 }
// 		outputfile<<(double) mag/lsqred<<"\n"; // schreibe Magnetisierungswert und File
// // 		mittelMag=mittelMag+mag;
// 	}
	
	cout<<"\n\n";
        printSpins();
// 	//WOLFF-ALGORITHMUS
//         thermalisieren();
// 	wolffAlgorithmus();
//         
//         
// 	//printf("Dauer: %f",float( clock () - begin_time )/  std::CLOCKS_PER_SEC);
        
	outputfile.close(); // schliesse File
    }
        return 0;
}
