#ifndef ANALYSE_H
#define ANALYSE_H

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

using namespace std;  // otherwise we would always have to write "std::vector" instead of just "vector"

vector<double> binnedjackknife(int binGroesse, vector<double> &messwerte){
//     if(sweeps%binGroesse!=0)
    vector<double> result(2);
    
    double mittelWert=0;
    double stdAbweichung=0;
    int vectorGroesse=sweeps/binGroesse;
    vector<double> binWerte(vectorGroesse,0.0);// erzeugt vektor mit lauer nullen
    vector<double> JKWerte(vectorGroesse,0.0);
    
    for(int i=0;i<sweeps;i++){
        binWerte[i/binGroesse]+=messwerte[i]/binGroesse;// i/binGroesse ist ein Integer! springt also automatisch weiter
    }
    
    for(int i=0;i<vectorGroesse;i++){
        for(int j=0;j<vectorGroesse;j++){
            JKWerte[i]+=binWerte[j];
        }
        JKWerte[i]=(JKWerte[i]-binWerte[i])/(vectorGroesse-1); // ziehen einen zu viel addierten Wert ab und Normieren
        mittelWert+=JKWerte[i]; // summieren mittelWert auf
    }
    
    mittelWert=mittelWert/vectorGroesse; //Normieren mittelWert
    result[0]=mittelWert;
    
    for(int i=0;i<vectorGroesse;i++){
        stdAbweichung+=pow(JKWerte[i]-mittelWert,2.);
    }
    result[1]=sqrt(stdAbweichung/vectorGroesse);
    
    return result;
}

#endif