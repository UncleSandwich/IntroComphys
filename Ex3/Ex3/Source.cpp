//Hoshen-Kopelman algorithm
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include "drand48.h"
#include<utility>

using namespace std;

#define PROBILITY 0.5
#define L 100

int main() {
	int M[L*L]{ 0 };
	int k=2;

	int lat[L*L];
	for (int icounter = 0; icounter < L*L; icounter++)
		lat[icounter] = drand48() < PROBILITY ? 1 : 0;

	int occupied = 0;
	for (int i = 0; i < L*L; i++) occupied += lat[i];
	cout << "Number of occupied sites: " << occupied << "\n";

	for (int i = 0; i < L; i++)
		for (int j = 0; j < L; j++) {
			if (lat[i*L + j] == 0) continue;
			else if (lat[i*L + j] == 1) {
				if (i == 0 && j == 0) {  //check whether the occupied site is on the left-top corner.
					lat[i*L + j] = k;    //if so, assign k=2
					M[lat[i*L + j]]++;
				}
				if (i == 0 && j > 0) { //check whether the occupied site is on the top row but not first.
					if (lat[i*L + (j - 1)] == 0) {
						k++;
						lat[i*L + j] = k;
						M[lat[i*L + j]]++;
					}
					else if (lat[i*L + (j - 1)] > 1) {
						int k0 = lat[i*L + (j - 1)];
						while (M[k0] < 0) k0 = -M[k0];
						lat[i*L + j] = k0;
						M[lat[i*L + j]]++;
					}
				}
				if (i > 0 && j == 0) { //check whether the occupied site is on the left periphery
					if (lat[(i - 1)*L + j] == 0) {
						k++;
						lat[i*L + j] = k;
						M[lat[i*L + j]]++;
					}
					else if (lat[(i - 1)*L + j] > 1) {
						int k0 = lat[(i - 1)*L + j];
						while (M[k0] < 0) k0 = -M[k0];
						lat[i*L + j] = k0;
						M[lat[i*L + j]]++;
					}
				}
				if (i > 0 && j > 0) { // for other sites in lattice
					if (lat[(i - 1)*L + j] == 0 && lat[i*L + (j - 1)] == 0) { // if top and left sites are empty
						k++;
						lat[i*L + j] = k;
						M[lat[i*L + j]]++;
					}
					else if (lat[(i - 1)*L + j] > 1 && lat[i*L + (j - 1)] == 0) { // if left is empty and top is occupied and belong to a cluster
						int k0 = lat[(i - 1)*L + j];
						while (M[k0] < 0) k0 = -M[k0];
						lat[i*L + j] = k0;
						M[lat[i*L + j]]++;
					}
					else if (lat[(i - 1)*L + j] == 0 && lat[i*L + (j - 1)] > 1) { //if top is empty and left is occupied and belong to a cluster
						int k0 = lat[i*L + (j - 1)];
						while (M[k0] < 0) k0 = -M[k0];
						lat[i*L + j] = k0;
						M[lat[i*L + j]]++;
					}
					else if (lat[(i - 1)*L + j] > 1 && lat[i*L + (j - 1)] > 1 ) { // if top and left are occupied 
						int k1 = lat[(i - 1)*L + j], k2 = lat[i*L + (j - 1)];
						while (M[k1] < 0) k1 = -M[k1];
						while (M[k2] < 0) k2 = -M[k2];
						if (k1 > k2) swap(k1, k2);
						
						lat[i*L + j] = k1;
						if (k1 != k2) {
							M[lat[i*L + j]] += M[k2] + 1;
							M[k2] = -k1;
						}
						else if (k1 == k2) 
							M[lat[i*L + j]]++;
					}
				}
					
				
			}
		}

	//cout << "Lattice clusters number\n";
	//for (int i = 0; i < L; i++) {
	//	for (int j = 0; j < L; j++) {
	//		cout << setw(5) << lat[i*L + j];
	//	}
	//	cout << "\n";
	//}

	// calculate the relative number of clusters with same size
	const int k_max = k;
	int N[L*L]{ 0 };
	for (int k = 2; k <= k_max; k++) {
		if (M[k] < 0) continue;
		N[M[k]]++;
	}
	
	int counter_occupied = 0;
	for (int i = 0; i < L*L; i++) {
		//cout << i << " : " << N[i] << "   ";
		counter_occupied += N[i] * i;
		//if (i % 10 == 0) cout << endl;
	}

	if (counter_occupied == occupied) cout << "Number of occupied sites match!\n";
	else cout << "Not match!\n";

	double n[L*L]{ 0 };
	for (int i = 0; i < L*L; i++) n[i] = N[i] / double(L*L);

	//for (int i = 0; i < L*L; i++) {
	//	cout << i << " : " << n[i] << "   ";
	//	if (i % 10 == 0) cout << "\n";
	//}

	cout << endl;
	system("pause");
	return 0;

}