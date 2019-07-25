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

double susPa1=-2.3661, susPa2=-9.001, susPa3=22.044;
double korelPa1=-1.0276, korelPa2=-0.8116, korelPa3=-11.3765;

int main(){
        double a=0,b=0,c=0,d=0,e=0,f=0,g=0,mm2=0,mm=0; // dumyvariable zum einlesen der Werte
        int number_of_configurations = leseStartfile(0,"./Messdaten/FSS/StartparameterFSS.txt") -1; // berechne anzahl der configurationen
//     cout<<"Anzahl an Konfigurationen : "<<number_of_configurations<<"\n";
        sprintf(file2,"./Messdaten/FSS/fss_Auswertung.txt");
        outputfile.open(file2,ios::out); //oeffne File
        outputfile<<"# Ausgewertete Messdaten aus Wolff-Algorithmus für FSS"<<endl;
        outputfile<<"# Parameter für Q-Funktionen: Susz. / Korrel. "<<endl;
        outputfile<<"# beta || Temperatur || Binderkumulante / Std.-Ab. || Suszeptibilitaet mit Clustergroesse / Std.-Ab. || Suszeptibilitaet Magnetisierungswerten / Std.-Ab.|| Korrelationslaenge / Std.-Ab."<<endl;
        sprintf(file1,"./Messdaten/FSS/MessgroessenFSS.txt");
        cout<<"Lese FILE: "<<file1<<endl;
        // vector<double> Ls(number_of_configurations);
        vector<double> betas(number_of_configurations);
        Auswertung binder;
        Auswertung sus1;
        Auswertung sus2;
        Auswertung korel;
        vector<double> x(number_of_configurations);

        ifstream datei(file1); // Messdaten aus Metropolisalgorithmus
        string zeile;
        int counter=0;
        // lesen Daten aus Wertetabelle ein
        while(getline(datei,zeile)){
            if(zeile[0]=='#'){
//                 counter++;
                continue;
            }
            stringstream zeilenpuffer(zeile);        
            zeilenpuffer>>a>>b>>c>>d>>e>>f>>g;
        //     Ls[counter]=a;
            betas[counter]=b;
            binder.messwerte.push_back(c);
            sus1.messwerte.push_back(d);
            sus2.messwerte.push_back(e);
            korel.messwerte.push_back(f);
            x[counter]=g;
            
            counter++;
                        
	}
        // berechne nötige Größen für Auswertung
        double anzahlBetas = count_unterschdl_Eintraege(betas);
        double reihen=(double) betas.size()/anzahlBetas;

        // Übergebe diese Größen an die Klassen
        binder.initialize(anzahlBetas,reihen);
        sus1.initialize(anzahlBetas,reihen);
        sus2.initialize(anzahlBetas,reihen);
        korel.initialize(anzahlBetas,reihen);

        //skaliere Suszeptibilität und co mit Q-Funktion
        sus1.skaliere(susPa1,susPa2,susPa3,x);
        sus2.skaliere(susPa1,susPa2,susPa3,x);
        korel.skaliere(korelPa1,korelPa2,korelPa3,x);
        //Analyse
        binder.analysiere();
        sus1.analysiere();
        sus2.analysiere();
        korel.analysiere();

        
        for(int i=0;i<anzahlBetas;i++){
                beta=betas[i];
                a=1/beta; // Temperatur bei gegebenem Beta
                outputfile<<beta<<"\t"<<a<<"\t"<<binder.mittelwerte[i]<<"\t"<<binder.stdA[i]<<"\t"<<sus1.mittelwerte[i]<<"\t"<<sus1.stdA[i]<<"\t"<<sus2.mittelwerte[i]<<"\t"<<sus2.stdA[i]<<"\t"<<korel.mittelwerte[i]<<"\t"<<korel.stdA[i]<<"\t"<<endl;
        }
    outputfile.close();
    return 0;
}