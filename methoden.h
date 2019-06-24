/*
 * methoden.h
 *
 *  Created on: May 8, 2019
 *      Author: rhtkue
 */

#ifndef METHODEN_H_
#define METHODEN_H_

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
#include "gitter.h"

int magnetisierung(){
    int result=0;
    for(int i=0;i<lsqred;i++){
        result+=spins[i];
    }
    return result;
}

double berechneImprovedEstimatorArgument(int position){//berechnen Argument aus improvedEstimator Formel
    double arg=kWert*(position%L);
    return arg; // siehe Formel fuer improvedEstimator
}

void metropolisflip(){
    int q=random_number()*lsqred; //zufaelliger Spin wird ausgesucht
    double deltaE=2*J*spins[q]*(spins[links[q]]+spins[rechts[q]]+spins[unten[q]]+spins[oben[q]]); // Eneu-Ealt
    double boltz=exp(-deltaE*beta);
    double w=fmin(1,boltz);
    if(random_number()<=w){
        spins[q]=-spins[q]; // wenn neue zufaellige Nummer kleiner ist als Wahrscheinlickeit w, wird der Spin an der Stelle q geflippt
        //Messgroessenupdates
        mag=mag+2*spins[q]; // update die Magnetisierung nach jedem Spinflip
    }
}

void metropolis(){
	for(int i=0;i<lsqred;i++){// for-schleife um einen Sweep zu bekommen, da zufaellige Spinauswahl genutzt wird
            metropolisflip();            
        }
        outputfile<<(double) mag/lsqred<<"\n";
}

void thermalisierenMETRO(int wiederholungen){
    for(int i=0;i<wiederholungen;i++){
        metropolisflip();
    }
}


void hinzufuegen(int r, int vz);

void findeCluster(int q, int vz){
	hinzufuegen(oben[q],vz);
	hinzufuegen(rechts[q],vz);
	hinzufuegen(unten[q],vz);
	hinzufuegen(links[q],vz);
}

void hinzufuegen(int r, int vz){
	if(spins[r]==vz && random_number()<=clusterWahrscheinlichkeit){ // Akzeptier-Kriterium
		spins[r]=-spins[r]; //flippen Spin
		clustergroesse++;
                sum_sin += sin(berechneImprovedEstimatorArgument(r));
                sum_cos += cos(berechneImprovedEstimatorArgument(r));
//                 cout<<"aktuelle Clustergroesse"<<clustergroesse<<"\n";
		findeCluster(r,vz);
	}
}


void wolffSweep_RE(){
	int geflippteSpins=0;
        int counter=0;
        mittelImprovedEstimator=0;
        mittelMag=0;
	while(geflippteSpins<lsqred){//wiederholung so lange bis im mittel L^2 Spins geflippt wurden
                clustergroesse=1; // =1 fuer den ersten gewaehlten Spin
                improvedEstimator=0.; // setzen Variable vor jeder WolffClusterberechnung auf 0
                sum_sin=0.; // setze sinus und cosinus von improvedEstimator berechnung auf 0
                sum_cos=0.;
                int q=random_number()*lsqred; //zufaelliger Spin wird ausgesucht
		int vz=spins[q]; //Vorzeichen von zufaelligem Spin
		spins[q]=-spins[q]; // flippen ersten Spin
		findeCluster(q,vz); // bauen restliches Cluster
//                 cout<<"Clustergroesse: "<<clustergroesse<<"\n";
		geflippteSpins+=clustergroesse;// berechne Anzahl an geflippten Spins insgesamt
                counter++; // Anzahl der Durchlaufe
                
                
		//MESSGROESSEN
		mag=mag-2*clustergroesse*vz;// minus weil altes vz verwendet wird
// 		mittelMag+=mag;
                improvedEstimator=pow(sum_cos,2.)+pow(sum_sin,2.); // quadrieren der sin und cos Summen im ImprovedEstimator
 		mittelImprovedEstimator+=improvedEstimator/clustergroesse;// sin cos Summer wird berechnet in jedem Schritt
		
		
// 		printSpins();
                /*
                cout<<"clustergr.: "<<clustergroesse;
                if(vz==1){
                    cout<<" (-)";
                }
                else{
                    cout<<" (+)";
                }
                cout<<" // flips insgesamt: "<<counter<<" // Magnetisierung: "<<mag<<"\n\n";*/
	}
// 	cout<<counter<<"\t"<<geflippteSpins<<"\n";
// 	mittelMag=mittelMag/counter;
        suszeptibilitaet+=geflippteSpins/counter;
        sum_counter+= counter;
// 	suszeptibilitaet=beta*geflippteSpins/counter; // formel mit G(0) aus Janke
//  	mittelSuszeptibilitaet+=suszeptibilitaet;
//        mittelImprovedEstimator=mittelImprovedEstimator/counter; // mittelwert fuer G(k)
        korrelationslaenge=1/(2*sin(kWert/2))*sqrt(geflippteSpins/mittelImprovedEstimator-1); // Formel Korrelationslaenge 1X COUNTER gekuerzt
}

void wolffAlgorithmus_RE(){
    for(int i=0;i<sweeps;i++){
//         cout<<"Sweep: "<<i<<"\n";
        wolffSweep_RE();
        outputfile<<setprecision(8)<< (double) mag/lsqred<<"\t"<<suszeptibilitaet<<"\t"<<korrelationslaenge<<"\t"<< (double) korrelationslaenge/L<<"\n";
    }
}

void thermalisierenWOLFF_RE(int wiederholungen){ // drop wolffSweeps um system zu thermalisieren
    for(int i=0;i<wiederholungen;i++){
        wolffSweep_RE();
        suszeptibilitaet=0.;
        sum_counter=0;
    }
}

void messung(){
  mag=magnetisierung();
  suszeptibilitaet+=cluster.size();
//   cout<<cluster.size()<<"\n";
}

bool inCluster(int index){
    for(int i=0;i<cluster.size();i++){
        if(cluster[i]==index){
            return true;
        } 
    }    
    return false;
}


void flippe_spins(){
    for(int i=0;i<cluster.size();i++){
        int index=cluster[i];
        spins[index]=-spins[index];
    }
}

void baueCluster(){
    int q=random_number()*lsqred; //zufaelliger Spin wird ausgesucht
    cluster.clear();
    cluster.push_back(q);
    vector<int> F_old;
    F_old.push_back(q);
    vector<int> nachbarn(4,0);
    while(!F_old.empty()){
        vector<int> F_new;
        for(int i=0;i<F_old.size();i++){
            int index=F_old[i];
            nachbarn[0]=oben[index];
            nachbarn[1]=rechts[index];
            nachbarn[2]=unten[index];
            nachbarn[3]=links[index];
            
            for(int j=0;j<4;j++){
                if(random_number()<clusterWahrscheinlichkeit && spins[nachbarn[j]]==spins[index] && !inCluster(nachbarn[j])){
                    
                    cluster.push_back(nachbarn[j]);
                    F_new.push_back(nachbarn[j]);
                    
                }
            }
        }
        F_old = F_new;
    }

void wolffSweep_IT(){
  int geflippteSpins=0;
  while(geflippteSpins<lsqred){
    baueCluster();
//     cout<<cluster[0]<<"\n";
    flippe_spins();
    geflippteSpins+=cluster.size();
  }
//   cout<<cluster.size()<<"\n";
//     cout<<"Clustergr. : "<<cluster.size()<<" // Magnetisierung : "<<magnetisierung()<<"\n";
}

void wolffAlgorithmus_IT(){
    for(int i=0;i<sweeps;i++){
//         cout<<"Sweep: "<<i<<"\n";
        wolffSweep_IT();
	messung();
        outputfile<<setprecision(8)<< (double) mag/lsqred<<"\n";//<<"\t"<<suszeptibilitaet<<"\t"<<korrelationslaenge<<"\t"<< (double) korrelationslaenge/L<<"\n";
    }
}

void thermalisieren_IT(){
  for(int i=0;i<drop;i++){
//         cout<<"Sweep: "<<i<<"\n";
        wolffSweep_IT();
    }
}





























#endif /* METHODEN_H_ */
