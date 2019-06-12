#ifndef CONSTANTEN_H
#define CONSTANTEN_H

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

using namespace std;  // otherwise we would always have to write "std::vector" instead of just "vector"



// definieren Konstanten
int L;	// Seitenlaenge des quadratischen Gitters
double J;	// Kopplungskonstantein Hamiltonian
// double T;	// Temperatur
// double k;		// Boltzmannkonstante -> Temperatur wird in Einheiten von k angegeben
double beta; //beta-wert

int sweeps; // Anzahl sweeps, entspricht Anzahl an einzelnen Werten die gemittelt werden
int drop; // Anzahl an Werten die nicht beruecksichtigt werden, bis System im Equlibrium ist

int lsqred; //Anzahl der Spins


char file1[100]; // char fuer File-Namen
char file2[100];
const char * startfilename={"./Startparameter.txt"};
ofstream outputfile;



// CLusterkonstanten
double clusterWahrscheinlichkeit;
int clustergroesse=0;



// definieren Vektoren fuer Spin und benachbarte Spins
vector<int> spins;
vector<int> oben;
vector<int> unten;
vector<int> links;
vector<int> rechts;

//Messgroessen
int mag;
double mittelMag=0.;
double improvedEstimator;
double mittelImprovedEstimator;
double kWert;
double suszeptibilitaet;
double mittelSuszeptibilitaet;
double korrelationslaenge;

void initialisiereVektoren(int laenge){
    vector<int> spinsNeu(laenge);
    vector<int> obenNeu(laenge);
    vector<int> untenNeu(laenge);
    vector<int> linksNeu(laenge);
    vector<int> rechtsNeu(laenge);
    
    spins=spinsNeu;
    oben=obenNeu;
    unten=untenNeu;
    rechts=rechtsNeu;
    links=linksNeu;
}

int leseStartfile(int config,const char* filename){
    //Einlesen der Werte aus "parameter.txt"
	ifstream datei(filename);
	string zeile;
        int counter=0;
        
	while(getline(datei,zeile)){
            if(zeile[0]=='#' || counter!=config){ // lasse nur eine bestimmte Configuration einlesen
                counter++;
                continue;
            }
            stringstream zeilenpuffer(zeile);        
            zeilenpuffer>>L>>J>>beta>>sweeps>>drop;
            counter++;
	}
	return counter;
}


void initialisiereKonstanten(int config){
    
	leseStartfile(config, startfilename);

	lsqred=pow(L,2); // berechne die Laenge der vektoren
//         beta=1/(k*T);
	clusterWahrscheinlichkeit=1-exp(-2*J*beta); // berechne die Wahrscheinlichkeit fuer den clusterflip
        
        kWert=2*M_PI/L; // k fuer den improvedEstimator,, um Rechenzeit zu sparen
        
        initialisiereVektoren(lsqred);
//         for(int i=0;i<lsqred;i++){
//             spins.push_back(i);
//             oben.push_back(i);
//             unten.push_back(i);
//             links.push_back(i);
//             rechts.push_back(i);
//         }
//         cout<<lsqred<<"\n"<<clusterWahrscheinlichkeit<<"\n"<<L<<"\n"<<T<<"\n"<<k<<"\n"<<J<<"\n";
}



#endif
