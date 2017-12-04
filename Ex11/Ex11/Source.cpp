#include<iostream>
#include<fstream>
#include<string>
#include<array>
#include <iomanip>
#include<time.h>

using namespace std;

#define x0 0.5
#define y0 0.5
#define N 500  //grid size, include boundary
#define dx 1./N
#define dy 1./N
#define rho_bound 0  //boundary condition
#define rho_charge 1./(dx*dy)  //density on the charge
#define threshold 0.00001

void Jacobi();
void Gauss();
void Gauss_multi();

int main() {
	//Task 1
	//Jacobi();

	//Task 2
	//Gauss();

	//Task 3
	Gauss_multi();

	//system("pause");
	return 0;
}

void Jacobi() {
	array<double, N*N> phi{ 0 };
	int i_nearest = 0, j_nearest = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			if (i == 0 || i == N - 1) {
				phi[i*N + j] = rho_bound;
			}
			if (j == 0 || j == N - 1) {
				phi[i*N + j] = rho_bound;
			}
			if (abs(i*dy - y0) < abs(i_nearest*dy - y0)) i_nearest = i;
			if (abs(j*dx - x0) < abs(j_nearest*dx - x0)) j_nearest = j;
		}
	bool isfixed = false;
	while (!isfixed)
	{
		array<double, N*N> phi_new = phi;
		for (int i = 1; i < N - 1; i++)
			for (int j = 1; j < N - 1; j++) {
				phi_new[i*N + j] = 0.25*(phi[(i + 1)*N + j] + phi[(i - 1)*N + j] + phi[i*N + (j + 1)] + phi[i*N + (j - 1)]) 
					+ (i == i_nearest && j == j_nearest)*0.25*dx*dy*rho_charge;
			}
		isfixed = 1;
		for (int m = 0; m < N*N; m++) {
			if (abs(phi_new[m] - phi[m]) > threshold) isfixed = 0;
		}
		if (!isfixed) phi = phi_new;
	}
	
	string filename = "JacobiN" + to_string(N) + "x0y0" + to_string(x0) + to_string(y0) + ".txt";
	fstream myfile(filename, ios::out | ios::trunc);
	for (int k = 0; k < N; k++)
		for (int l = 0; l < N; l++)
		{
			if ((k*N + l) % N == 0) myfile << "\n";
			myfile << setw(10) << phi[k*N + l] << " ";
		}
	myfile.close();

}

void Gauss() {
	array<double, N*N> phi{ 0 };
	int i_nearest = 0, j_nearest = 0;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			if (i == 0 || i == N - 1) {
				phi[i*N + j] = rho_bound;
			}
			if (j == 0 || j == N - 1) {
				phi[i*N + j] = rho_bound;
			}
			if (abs(i*dy - y0) < abs(i_nearest*dy - y0)) i_nearest = i;
			if (abs(j*dx - x0) < abs(j_nearest*dx - x0)) j_nearest = j;
		}
	bool isfixed = false;
	int update_counter = 0;
	while (!isfixed)
	{
		for (int i = 1; i < N - 1; i++)
			for (int j = 1; j < N - 1; j++) {
				phi[i*N + j] = 0.25*(phi[(i + 1)*N + j] + phi[(i - 1)*N + j] + phi[i*N + (j + 1)] + phi[i*N + (j - 1)])
					+ (i == i_nearest && j == j_nearest)*0.25*dx*dy*rho_charge;
			}
		update_counter++;
		if (update_counter > 10000) isfixed = 1;
	}

	string filename = "GaussN" + to_string(N) + "x0y0" + to_string(x0) + to_string(y0) + ".txt";
	fstream myfile(filename, ios::out | ios::trunc);
	for (int k = 0; k < N; k++)
		for (int l = 0; l < N; l++)
		{
			if ((k*N + l) % N == 0) myfile << "\n";
			myfile << setw(10) << phi[k*N + l] << " ";
		}
	myfile.close();
}

void Gauss_multi() {
	array<double, N*N> phi{ 0 };
	array<double, N*N> charge{ 0 };

	//initialize the phi field
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			if (i == 0 || i == N - 1) {
				phi[i*N + j] = rho_bound;
			}
			if (j == 0 || j == N - 1) {
				phi[i*N + j] = rho_bound;
			}
		}

	//initialize the charge position
	int charge_number = 10;
	srand(time(NULL));
	for (int m = 0; m < charge_number; m++) {
		int i = rand() % (N - 4) + 2;
		int j = rand() % (N - 4) + 2;
		charge[i*N + j] = 1;
	}

	bool isfixed = false;
	int update_counter = 0;
	while (!isfixed)
	{
		for (int i = 1; i < N - 1; i++)
			for (int j = 1; j < N - 1; j++) {
				phi[i*N + j] = 0.25*(phi[(i + 1)*N + j] + phi[(i - 1)*N + j] + phi[i*N + (j + 1)] + phi[i*N + (j - 1)])
					+ charge[i*N + j] * 0.25*dx*dy*rho_charge;
			}
		update_counter++;
		if (update_counter > 10000) isfixed = 1;
	}

	string filename = "GaussMultiN" + to_string(N) + "charge" + to_string(charge_number) + ".txt";
	fstream myfile(filename, ios::out | ios::trunc);
	for (int k = 0; k < N; k++)
		for (int l = 0; l < N; l++)
		{
			if ((k*N + l) % N == 0) myfile << "\n";
			myfile << setw(10) << phi[k*N + l] << " ";
		}
	myfile.close();
}