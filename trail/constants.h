/* defining constants for the isingmodel */
#define N 16							/* lattice size N*N */
#define Measurements 10000 			/* number of iterations */
#define EquilibriumWait 50				/* number of iterations until equilibrium */
#define BetweenMeasurements 50			/* iterations between measurements */
#define J 1.0 							/* coupling constant */
#define temp_start 2.0 					/* starting temperature for the sweep */
#define PI acos(-1.0)


short nn;								/* nearest neighbour counting for the metropolis algorithm */
short s[N][N];							/* spin lattice */
short cluster[N][N];					/* saves the current cluster for the wolff algorithm */
short si; 								/* value of a single spin */
double beta=0.425;							/* inverse temperature */
// double boltzmann[2][9];					/* contains the boltzmann factors for the metropolis algorithm */
double temperature;						/* temperature */
double clusterprobability;				/* saves the probability of a spin getting added to the cluster */
double g_k;
double g_0;
int clustersize;						/* saves the clustersize */
int mode;								/* sets the mode used: Metropolis or Wolff algorithm */
double impsscorr[N];
double sscorr[N];
double magnet1;							/* saves the expectation value of M */
double magnet2;							/* saves the expectation value of M^2 */
double magnet4;							/* saves the expectation value of M^4 */
double energy1;							/* saves the expectation value of E */
double energy2;							/* saves the expectation value of E^2 */
double energy;							/* saves the expectation value of E */
char ising2d[]= "./100x100/";      	    /* Filename */
char corr[]= "./100x100_1/";			/* Notfall */
char fileending[] = ".dat";				/* File ending */
// FILE *fp;								/* Files */
// FILE *fp1;
char file1[100];
std::ofstream outputfile;