#include<iostream>
#include<fstream>
#include<string>
#include<array>
#include <iomanip>
#include<time.h>
#include "Eigen\Dense"

using namespace std;
using namespace Eigen;

#define x0 0.5
#define y0 0.5
#define N 10  //grid size, include boundary
#define dx 1./N
#define dy 1./N
#define rho_bound 0  //boundary condition
#define rho_charge 1./(dx*dy)  //density on the charge
#define threshold 0.01

int main() {
	MatrixXf phi = MatrixXf::Zero(N, N);
	int i_nearest = 0, j_nearest = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			if (i == 0 || i == N - 1) {
				phi(i, j) = rho_bound;
			}
			if (j == 0 || j == N - 1) {
				phi(i, j) = rho_bound;
			}
			if (abs(i*dy - y0) < abs(i_nearest*dy - y0)) i_nearest = i;
			if (abs(j*dx - x0) < abs(j_nearest*dx - x0)) j_nearest = j;
		}

	MatrixXf A = MatrixXf::Zero((N-2)*(N-2), (N - 2)*(N - 2));
	VectorXf b = VectorXf::Zero((N - 2)*(N - 2));
	VectorXf Phi = VectorXf::Zero((N - 2)*(N - 2));
	for (int i = 1; i < N-1; i++)
		for (int j = 1; j < N-1; j++) {
			int k = i + (j - 1)*(N - 2) - 1; //minus 1 to start Phi at number 0
			Phi(k) = phi(i, j);
	}
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			int k = i + (j - 1)*(N - 2) - 1; //minus 1 to start Phi at number 0
			if (i == 0 || i == N - 1) {
				b(k) -= rho_bound;
			}
			if (j == 0 || j == N - 1) {
				b(k) -= rho_bound;
			}
	}
	for (int k = 0; k < (N - 2)*(N - 2); k++) {
		int i = k % (N - 2);
		int j = (k - i) / (N - 2);
		i -= 1;
		j -= 1;
		A(k, k) = -4;
		

		if (i - 1 == 0 || i + 1 == N - 1) {
			b(k) -= rho_bound;
		}
		if (j - 1 == 0 || j + 1 == N - 1) {
			b(k) -= rho_bound;
		}
	}

}