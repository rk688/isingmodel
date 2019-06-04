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

int main(){
    char filename[100];
//     cout<<"Filname eingeben:\t";
//     cin>>filename;
    ifstream datei("./Messdaten/METRO_Werte_L_50_beta_0.400.txt"); // Messdaten aus Metropolisalgorithmus
    string zeile;
    int counter=0, order=200;
    double a,mm=0,mm2=0;
    vector<double> x; // vector fuer alle Messwerte
    ofstream outputfile("./Messdaten/Autokorrelationdaten.txt",ios::out); //oeffne File
        
    while(getline(datei,zeile)){
        if(zeile[0]=='#'){ // in der Datei sollten keine Zeilen it # sein...
                counter++;
                continue;
        }
        stringstream zeilenpuffer(zeile);        
        zeilenpuffer>>a;
        x.push_back(a);
        counter++;
//         mm+=a; // addieren Magnetisierungen auf fuer einen Mittelwert
//         mm2+=a*a; //addieren quadratische Magnetisierungswerte
	}
//     mm=mm/counter; //bilden Mittelwert der Magnetisierung
//     mm2=mm2/counter;// bilden Mittelwert der quadratischen Magnetisierung
    
//     bilden Autokorrelation analog zur Formel 4.62/S.103 und unter 4.57/S. 102 im Text aus Janke:
//     A(k)=<A_i*A_i+1>-<A_i><A_i+k>/<A_1^2>-<A_i>^2
//     (order=k im Code)
    for(int i=0;i<order;i++){
        double sum1=0,sum2=0, sum3=0, sum4=0, nenner=0,zaehler=0;
        for(int j=0;j<(counter-i);j++){
            sum1+=x[j]*x[j+i];
            sum2+=x[j];
            sum3+=x[j+i];
            sum4+=x[j]*x[j];
        }
        zaehler=sum1-sum2*sum3/(counter-i);
        nenner=sum4-sum2*sum2/(counter-1);
        outputfile<<zaehler/nenner<<"\n"; //kuerzen einmal 1/(counter-i)!
    }
    
	
//     for(int i=0;i<order;i++){
//         cout<<x[i]<<"\n";
//         double sum=0;
//         double sum1=0;
//         double sum2=0;
//         double sum3=0;
//         for(int j=0;j<(order-i);j++){
//             sum+=x[j]*x[j+i];
//             sum1+=x[j];
//             sum2+=x[j+i];
//             sum3+=x[j]*x[j];
//         }
//         outputfile<<fabs((sum-sum1*sum2/(order-i))/(sum3-sum1*sum1/(order-i)))<<"\n";
//     }
    outputfile.close();
    cout<<counter<<" done\n";
    return 0;
}