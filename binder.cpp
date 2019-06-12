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
#include <iomanip>
#include "constanten.h"
#include "analyse.h"

using namespace std;  // otherwise we would always have to write "std::vector" instead of just "vector"

// vector<double> binnedjackknife;

int main(){
    int number_of_configurations = leseStartfile(0,startfilename) -1; // berechne anzahl der configurationen
    cout<<"Anzahl an Konfigurationen : "<<number_of_configurations<<"\n";
    sprintf(file2,"./Messdaten/Binderkumulanten.txt");
    outputfile.open(file2,ios::out); //oeffne File
    outputfile<<"# beta // kumulante U  // L\n"; // schreibe groessen an den anfang des files
    
    double a,b; // dumyvariable zum einlesen der Werte
    
    int binGroesse=10;
    vector<double> resultsmm2(2);
    vector<double> resutlsmm4(2);
         
    for(int i=1;i<=number_of_configurations;i++){
        leseStartfile(i,startfilename);
        sprintf(file1,"./Messdaten/WOLFF_Werte_L_%d_beta_%.3f_sweeps_%d_drops_%d.txt",L,beta,sweeps,drop);
        lsqred=L*L;
        
        vector<double> mag2(sweeps);
        vector<double> mag4(sweeps);
        
        ifstream datei(file1); // Messdaten aus Metropolisalgorithmus
        string zeile;
        int counter=0;
        // lesen Daten aus Wertetabelle ein
        while(getline(datei,zeile)){
            stringstream zeilenpuffer(zeile);        
            zeilenpuffer>>b;
            a=b/lsqred;// um mag-werte zu mitteln
            mag2[counter]=(a*a);
            mag4[counter]=pow(a,4.);
            counter++;
	}
	
	resultsmm2=binnedjackknife(binGroesse,mag2);
        resutlsmm4=binnedjackknife(binGroesse,mag4);
	
//     BINDERKUMULANTE 4. ORDNUNG
//     nach Formel 4.95 Janke S115
//     U(beta)=1-<mag^4>/3/<mag^2>^2
        
        
        
        
// //         HIER NOCH OHNE BINNEDJACKKNIF
//         double mag2=0,mag4=0, sum=0; // quadratische und hoch 4 Magnetisierungswerte
//         for(int i=0;i<counter;i++){
//             sum=x[i]*x[i];
//             mag2+=sum;
//             mag4+=sum*sum;
//         }
    
    
        double zaehler=resutlsmm4[0];
        double nenner=resultsmm2[0]*resultsmm2[0]*3;
//         cout<<"BINDERKUMULANTE: "<<1.-zaehler/nenner<<"\n";
        outputfile<<std::fixed << std::setprecision(10)<<beta<<"\t"<<(double) 1.-zaehler/nenner<<"\t"<<L<<"\n";
    }
    outputfile.close();
    cout<<"... done\n";
    return 0;
}