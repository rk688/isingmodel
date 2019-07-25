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

vector<double> binnedjackknife(int binGroesse, int counter ,vector<double> &messwerte){
//     if(sweeps%binGroesse!=0)
    vector<double> result(2);
    
    double mittelWert=0;
    double stdAbweichung=0;
    int vectorGroesse=counter/binGroesse;
    vector<double> binWerte(vectorGroesse,0.0);// erzeugt vektor mit lauer nullen
    vector<double> JKWerte(vectorGroesse,0.0);
    
    for(int i=0;i<counter;i++){
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


class Auswertung{ 
    // Access specifier 
    public: 
  
    // Messwerte 
    vector<double> messwerte; 
    // Mittelwerte
    vector<double> mittelwerte;
    // Standardabweichungen
    vector<double> stdA;
    // Anzahl unterschiedlicher Ls für ein beta um Mittelwerte zubilden
    int reihen;
    //Anzahl unterschiedlicher betas
    int anzahlBetas;
    // Member Functions()
    void initialize(int number1, int number2){
        anzahlBetas=number1;
        reihen=number2;
    }

    void printParameter(){
        cout<<"reihen: "<<reihen<<endl;
        cout<<"anzahlBetas: "<<anzahlBetas<<endl;
    }

    void analysiere(){
        berechne_mittelwerte();
        berechne_stdA();
    }

    void skaliere(double pa1, double pa2, double pa3, vector<double> &x){
        int size=messwerte.size();
        for(int i=0;i<size;i++){
            double xi=x[i];
            double Q=1+pa1*exp(-1/xi)+pa2*exp(-2/xi)+pa3*exp(-3/xi);
            messwerte[i]=messwerte[i]/Q;
        }
    }

    private:

    void berechne_mittelwerte(){
        int size=messwerte.size();
        for(int i=0;i<anzahlBetas;i++){
            double wert=0;
            for(int j=i;j<size;j+=anzahlBetas){
                wert+=messwerte[j];
            }
            wert=wert/reihen;
            mittelwerte.push_back(wert);
        }

    }

    void berechne_stdA(){
       int size=messwerte.size();
        for(int i=0;i<anzahlBetas;i++){
            double wert=0;
            for(int j=i;j<size;j+=anzahlBetas){
                wert+=pow((messwerte[j]-mittelwerte[i]),2.);
            }
            wert=sqrt(wert/reihen);
            stdA.push_back(wert);
        }
    }
};

double count_unterschdl_Eintraege(vector<double> &vec){
    int size = vec.size();
    double check;
    vector<double> temp;
    temp.push_back(vec[0]); //vector zum abspeichern der verschiedenen Elemente in betas
    for(int i=1;i<size;i++){
        check=vec[i];
        if(find(temp.begin(),temp.end(),check)==temp.end()) temp.push_back(check); // kontrolliere ob check schon in temp vorhanden ist
    }
    check=temp.size();
    return check;
}

#endif