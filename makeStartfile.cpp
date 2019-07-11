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
    outputfile<<"#Laenge L // Kopplungskonstante J // Beta // sweeps // drop // zwischenMessungen\n";
    int Ls[]={100,150,200,250,300,350,400,450,500};//;{16,20,25,30,35,40,50,60,70,80,90,100,120,150};
    double betaStart=0.44065, betaEnde=0.44085, deltaBeta=0.00005;
    sweeps=50000;
    drop=10000;
    zwischenMessungen=10;
    
    int counter=sizeof(Ls)/sizeof(Ls[0]);
    for(int i=0;i<counter;i++){
        double beta=betaStart;
        while(beta<=betaEnde){
            outputfile<<Ls[i]<<"\t"<<(double) 1.0<<"\t"<<beta<<"\t"<<sweeps<<"\t"<<drop<<"\t"<<zwischenMessungen<<"\n";
            beta+=deltaBeta;
        }
//         outputfile<<Ls[i]<<"\t"<<(double) 1.0<<"\t"<<0.440675<<"\t"<<sweeps<<"\t"<<drop<<"\t"<<zwischenMessungen<<"\n";
//         outputfile<<Ls[i]<<"\t"<<(double) 1.0<<"\t"<<0.440725<<"\t"<<sweeps<<"\t"<<drop<<"\t"<<zwischenMessungen<<"\n";
    }
    outputfile.close();
    return 0; 
}