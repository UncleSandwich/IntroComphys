#include<iostream>
#include<fstream>
#include<string>
#include"drand48.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include<algorithm>

using namespace std;

#define LATTICE_SIZE 101
#define UP 1
#define DOWN -1
#define J 1
#define k_B 1

int main() {
	double T; //temperature
	int lat[LATTICE_SIZE*LATTICE_SIZE];
	fill_n(lat, LATTICE_SIZE*LATTICE_SIZE, UP);
	int energy_change[]{ -2 * J, 2 * J }; //possible energy change between two cells
	float E{0}; //Energy of the whole lattice
	int M{LATTICE_SIZE*LATTICE_SIZE}; //Magnetization of the whole lattice

	/*string filename = "L=" + to_string(LATTICE_SIZE)+".txt";
	fstream myfile(filename, ios::out | ios::trunc);*/
	
	for (T = 2; T < 2.01; T += 0.01) {
		string filename = "L=" + to_string(LATTICE_SIZE) + " T=" + to_string(T) + ".txt";
		fstream myfile(filename, ios::out | ios::trunc);
		double E_over_M{ 0 };
		double E_mean = 0;
		double M_mean = 0;

		const int sweeps = 100; //steps to leave out correlation
		long MC_step = sweeps*LATTICE_SIZE*LATTICE_SIZE*0.2; //steps of Monte Carlo sampling
		srand(time(NULL));
		srand48(time(NULL));
		for (long n = 1; n < (MC_step + 1); n++) {
			//the coordinate of the cell to be fliped
			int cell_flip_i = rand() % LATTICE_SIZE;
			int cell_flip_j = rand() % LATTICE_SIZE;

			//cout << "i,j: " << cell_flip_i << " " << cell_flip_j << "\n";

			int delta_E = 0; //total energy change of this flip

			int up_i;
			if (cell_flip_i != 0) up_i = cell_flip_i - 1;
			else up_i = LATTICE_SIZE - 1;
			if (lat[cell_flip_i*LATTICE_SIZE + cell_flip_j] == lat[up_i*LATTICE_SIZE + cell_flip_j]) delta_E += energy_change[1];
			else delta_E += energy_change[0];

			int down_i;
			if (cell_flip_i != LATTICE_SIZE - 1) down_i = cell_flip_i + 1;
			else down_i = 0;
			if (lat[cell_flip_i*LATTICE_SIZE + cell_flip_j] == lat[down_i*LATTICE_SIZE + cell_flip_j]) delta_E += energy_change[1];
			else delta_E += energy_change[0];

			int left_j;
			if (cell_flip_j != 0) left_j = cell_flip_j - 1;
			else left_j = LATTICE_SIZE - 1;
			if (lat[cell_flip_i*LATTICE_SIZE + cell_flip_j] == lat[cell_flip_i*LATTICE_SIZE + left_j]) delta_E += energy_change[1];
			else delta_E += energy_change[0];

			int right_j;
			if (cell_flip_j != LATTICE_SIZE - 1) right_j = cell_flip_j + 1;
			else right_j = 0;
			if (lat[cell_flip_i*LATTICE_SIZE + cell_flip_j] == lat[cell_flip_i*LATTICE_SIZE + right_j]) delta_E += energy_change[1];
			else delta_E += energy_change[0];

			//cout << "delta_E: " << delta_E << "\n";

			//accept according to acceptence probability
			if (delta_E <= 0) lat[cell_flip_i*LATTICE_SIZE + cell_flip_j] *= -1;
			else {
				int action = exp(-delta_E / T) > drand48() ? -1 : 1;
				lat[cell_flip_i*LATTICE_SIZE + cell_flip_j] *= action;
			}



			if (n % sweeps == 0) {
				//cout << "n: " << n << "\n";
				//calculate the total energy
				E = 0;
				for (int i = 0; i < LATTICE_SIZE; i++)
					for (int j = 0; j < LATTICE_SIZE; j++) {

						if (i != 0) up_i = i - 1;
						else up_i = LATTICE_SIZE - 1;
						E += -J*lat[i*LATTICE_SIZE + j] * lat[up_i*LATTICE_SIZE + j];

						if (i != LATTICE_SIZE - 1) down_i = i + 1;
						else down_i = 0;
						E += -J*lat[i*LATTICE_SIZE + j] * lat[down_i*LATTICE_SIZE + j];

						if (j != 0) left_j = j - 1;
						else left_j = LATTICE_SIZE - 1;
						E += -J*lat[i*LATTICE_SIZE + j] * lat[i*LATTICE_SIZE + left_j];

						if (j != LATTICE_SIZE - 1) right_j = j + 1;
						else right_j = 0;
						E += -J*lat[i*LATTICE_SIZE + j] * lat[i*LATTICE_SIZE + right_j];
					}
				E /= 2.;
				E_mean += E;
				//cout << "E: " << E << "\n";

				//calculate the magnetization
				M = 0;
				for (int i = 0; i < LATTICE_SIZE; i++)
					for (int j = 0; j < LATTICE_SIZE; j++) {
						M += lat[i*LATTICE_SIZE + j];
					}
				M = abs(M);
				M_mean += M;
				//cout << "M: " << M << "\n";

				E_over_M += E / M;

				myfile << n << " " << M << "\n";

				/*for (int i = 0; i < LATTICE_SIZE; i++)
				for (int j = 0; j < LATTICE_SIZE; j++) {
				if ((i*LATTICE_SIZE + j) % LATTICE_SIZE == 0) cout << "\n";
				cout << lat[i*LATTICE_SIZE + j] << " ";
				}
				cout << endl;*/
			}
		}
		E_mean /= MC_step / sweeps;
		M_mean /= MC_step / sweeps;
		E_over_M /= MC_step / sweeps;
		//cout << "E_mean: " << E_mean << "  M_mean: " << M_mean << "  E/M: " << E_over_M << "  T: " << T << "\n";
		//myfile << E_mean << "  " << M_mean << "  " << E_over_M << "  " << T << "\n";
		myfile.close();
	}
	

	//system("pause");
	return 0;
}