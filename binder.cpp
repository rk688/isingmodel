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
#include "analyse.h"

using namespace std;  // otherwise we would always have to write "std::vector" instead of just "vector"

// vector<double> binnedjackknife;

int main(){
    int number_of_configurations = leseStartfile(0,startfilename) -1; // berechne anzahl der configurationen
    cout<<"Anzahl an Konfigurationen : "<<number_of_configurations<<"\n";
    
    
    double a,mm2=0,mm=0; // dumyvariable zum einlesen der Werte

    int binGroesse=10;
    vector<double> resultsmm(2);
    vector<double> resultsmm2(2);
    vector<double> resutlsmm4(2);
    
    sprintf(file2,"./Messdaten/Binderkumulanten.txt");
    outputfile.open(file2,ios::out); //oeffne File
    outputfile<<"# beta // kumulante U  // L\n"; // schreibe groessen an den anfang des files
//     outputfile<<"# beta // Magnetisierungswerte\n";
    
    for(int i=1;i<=number_of_configurations;i++){
        leseStartfile(i,startfilename);
        sprintf(file1,"./Messdaten/WOLFF_Werte_L_%d_beta_%.3f_sweeps_%d_drops_%d.txt",L,beta,sweeps,drop);
        cout<<file1<<"\t";
        ifstream datei(file1); // Messdaten aus Metropolisalgorithmus
        string zeile;
//         vector<double> mag(sweeps);
        vector<double> mag2(sweeps);
        vector<double> mag4(sweeps);
        int counter=0;
        // lesen Daten aus Wertetabelle ein
        while(getline(datei,zeile)){
            if(zeile[0]=='#'){
                counter++;
                continue;
            }
            stringstream zeilenpuffer(zeile);        
            zeilenpuffer>>a;
//             mag[counter-1]=fabs(a);
            mag2[counter-1]=a*a;
            mag4[counter-1]=pow(a,4.);
            counter++;
	}
	cout<<counter<<"\n";
// 	resultsmm=binnedjackknife(binGroesse,mag);
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
    
//         cout<<"Mittlere Suszeptibilitaet: "<<beta*(resultsmm2[0]-pow(resultsmm[0],2.))<<"\n";
        double zaehler=resutlsmm4[0];
        double nenner=resultsmm2[0]*resultsmm2[0]*3;
//         cout<<"BINDERKUMULANTE: "<<1.-zaehler/nenner<<"\n";
        outputfile<<setprecision(8)<<beta<<"\t"<<(double) 1.-zaehler/nenner<<"\t"<<L<<"\n";
//         outputfile<<beta<<"\t"<<resultsmm[0]<<"\n";
    }
    outputfile.close();
    cout<<"... done\n";
    return 0;
}