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
    ifstream datei("./Messdaten/WerteL_50beta_0.400.txt");
    string zeile;
    int counter=0, order=20;
    double a,mm=0,mm2=0;
    vector<double> x;
    ofstream outputfile("./Messdaten/Autokorrelationdaten.txt",ios::out); //oeffne File
        
    while(getline(datei,zeile)){
        if(zeile[0]=='#'){
                counter++;
                continue;
        }
        stringstream zeilenpuffer(zeile);        
        zeilenpuffer>>a;
        x.push_back(a);
        counter++;
        mm+=a;
        mm2+=a*a;
	}
    mm=mm/counter;
    mm2=mm2/counter;
    for(int i=0;i<order;i++){
        double sum=0;
        for(int j=0;j<(counter-i);j++){
            sum+=x[j]*x[j+i];
        }
        outputfile<<(sum/(counter-i)-mm*mm)<<"\n";
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