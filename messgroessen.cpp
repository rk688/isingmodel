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

int main(){
    int number_of_configurations = leseStartfile(0,startfilename) -1; // berechne anzahl der configurationen
    cout<<"Anzahl an Konfigurationen : "<<number_of_configurations<<"\n";

    // Öffne neuen Outputfile
    sprintf(file2,"./Messdaten/Messgroessen.txt");
    outputfile.open(file2,ios::out); //oeffne File
    outputfile<<"# Ausgewertete Messdaten aus Wolff-Algorithmus"<<endl;
    outputfile<<"# L || beta || Binderkumulante ||  Suszeptibilitaet mit Clustergroesse || Suszeptibilitaet Magnetisierungswerten || Korrelationslaenge || x"<<endl;

    double a=0,b=0,c=0,d=0,e=0,mm2=0,mm=0; // dumyvariable zum einlesen der Werte
    int binGroesse=10000;

    //vektoren für ergebnisse
    vector<double> resultsMag(2);
    vector<double> resultsMag2(2);
    vector<double> resultsMag4(2);
    vector<double> resultsClust(2);
    vector<double> resultsGk(2);

    for(int i=1;i<=number_of_configurations;i++){
        leseStartfile(i,startfilename);
        sprintf(file1,"./Messdaten/FSS/WOLFF_Werte_L_%d_beta_%.6f_sweeps_%d_drops_%d.txt",L,beta,sweeps,drop);
        cout<<"Lese FILE: "<<i<<" / "<<number_of_configurations<<endl<<file1<<endl;
        lsqred=L*L;

        // Vektoren für Messwerte
        vector<double> mag(sweeps);
        vector<double> mag2(sweeps);
        vector<double> mag4(sweeps);
        vector<double> clust(sweeps);
        vector<double> Gk(sweeps);

        // lesen Daten aus file ein
        ifstream datei(file1);
        string zeile;
        int counter=0;
        while(getline(datei,zeile)){
            if(zeile[0]=='#'){ // ignorieren Kopf der Datei
                continue;
            }
            stringstream zeilenpuffer(zeile);        
            zeilenpuffer>>a>>b>>c>>d>>e;
            mag[counter]=a;
            mag2[counter]=b;
            mag4[counter]=c;
            clust[counter]=d;
            Gk[counter]=e;
            counter++;
	}
        // Nutze Binned-Jackknife um Auto und Kreuzkorrelation zu verringern
	resultsMag=binnedjackknife(binGroesse,mag);
	resultsMag2=binnedjackknife(binGroesse,mag2);
        resultsMag4=binnedjackknife(binGroesse,mag4);
        resultsClust=binnedjackknife(binGroesse,clust);
        resultsGk=binnedjackknife(binGroesse,Gk);

//     BINDERKUMULANTE 4. ORDNUNG
//     nach Formel 4.95 Janke S115
//     U(beta)=1-<mag^4>/3/<mag^2>^2
//         a=beta*lsqred*(resultsmm2[0]-pow(resultsmm[0],2));
        a=1-resultsMag4[0]/3/pow(resultsMag2[0],2.);
        // Suszeptibilität mit Clustergröße
        b=resultsClust[0];
        // Suszeptibilität mit Magnetisierung
        c=lsqred*(resultsMag2[0]-pow(resultsMag[0],2.));
        // Imporved Estimator
        d=1/(2*sin(M_PI/L))*sqrt(resultsClust[0]/resultsGk[0]-1);
        // x-wert
        e=d/L;
        outputfile<<L<<"\t"<<beta<<"\t"<<a<<"\t"<<b<<"\t"<<c<<"\t"<<d<<"\t"<<e<<endl;
    }
    outputfile.close();
    return 0;
}