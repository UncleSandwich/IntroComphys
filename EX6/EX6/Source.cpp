#include<iostream>
#include<fstream>
#include<string>
#include"drand48.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

#define LATTICE_SIZE 50
#define UP 1
#define DOWN -1
#define J 1
#define k_B 1

int main() {
	double T = 1; //temperature
	int lat[LATTICE_SIZE*LATTICE_SIZE]{ UP };
	int energy_change[]{ 2 * J, -2 * J }; //possible energy change between two cells
	int E{LATTICE_SIZE*LATTICE_SIZE}; //Energy of the whole lattice
	int M{LATTICE_SIZE*LATTICE_SIZE}; //Magnetization of the whole lattice

	const int sweeps = 100;
	long MC_step = sweeps*LATTICE_SIZE*LATTICE_SIZE; //steps of Monte Carlo sampling, 100 sweeps
	srand(time(NULL));
	srand48(time(NULL));
	for (long n = 0; n < MC_step; n++) {
		//the coordinate of the cell to be fliped
		int cell_flip_i = rand() % LATTICE_SIZE; 
		int cell_flip_j = rand() % LATTICE_SIZE;

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

		//accept according to acceptence probability
		if (delta_E <= 0) lat[cell_flip_i*LATTICE_SIZE + cell_flip_j] *= -1;
		else {
			int action = exp(-delta_E / T) > drand48() ? -1 : 1;
			lat[cell_flip_i*LATTICE_SIZE + cell_flip_j] *= action;
		}

		if (n % (LATTICE_SIZE*LATTICE_SIZE) == 0) {
			
		}
	}

	system("pause");
	return 0;
}