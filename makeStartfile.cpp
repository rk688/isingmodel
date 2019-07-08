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

using namespace std;  // otherwise we would always have to write "std::vector" instead of just "vector"

int main(){
    outputfile.open(startfilename,ios::out); //oeffne File
    outputfile<<"#Laenge L // Kopplungskonstante J // Beta // sweeps // drop\n";
    int Ls[]={16};//,18,20,22,25,27,30,32,34,36,40,50,60,70,80,100,110,150};
    double betaStart=0.425, betaEnde=0.425, deltaBeta=0.00005;
    sweeps=50000;
    drop=1000;
    zwischenMessungen=10;
    
    int counter=sizeof(Ls)/sizeof(Ls[0]);
    for(int i=0;i<counter;i++){
        double beta=betaStart;
        while(beta<=betaEnde){
            outputfile<<Ls[i]<<"\t"<<(double) 1.0<<"\t"<<beta<<"\t"<<sweeps<<"\t"<<drop<<"\t"<<zwischenMessungen<<"\n";
            beta+=deltaBeta;
        }
    }
    outputfile.close();
    return 0;
}