#include<iostream>
#include<fstream>
#include<string>
#include<array>
#include <iomanip>
#include<time.h>
#include "Eigen\Dense"
#include "Eigen\SparseCore"

using namespace std;
using namespace Eigen;

tuple<int, int> ij(int);

#define x0 0.5
#define y0 0.5
#define N 10  //grid size, include boundary
#define dx 1./N
#define dy 1./N
#define rho_bound 0  //boundary condition
#define rho_charge_times_dxdy 1  //density on the charge
#define threshold 0.00001

int main() {
	MatrixXd phi = MatrixXd::Zero(N, N);
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

	//MatrixXd A = MatrixXd::Zero((N - 2)*(N - 2), (N - 2)*(N - 2));
	SparseMatrix<double> A((N - 2)*(N - 2), (N - 2)*(N - 2));
	A.reserve(VectorXi::Constant((N - 2)*(N - 2), 6));
	VectorXd b = VectorXd::Zero((N - 2)*(N - 2));
	VectorXd Phi = VectorXd::Zero((N - 2)*(N - 2));

	int k_charge = i_nearest + (j_nearest - 1)*(N - 2);
	b(k_charge - 1) += rho_charge_times_dxdy;


	for (int i = 1; i <= N-2; i++)
		for (int j = 1; j <= N-2; j++) {
			int k = j + (i - 1)*(N - 2);
			A.insert(k-1, k-1) = -4;
		
			if (i - 1 == 0) {
				b(k-1) -= rho_bound;
			}
			else {
				A.insert(k - 1, k  - N + 2 - 1) = 1;
			}

			if ( i + 1 == N - 1) {
				b(k - 1) -= rho_bound;
			}
			else {
				A.insert(k - 1, k + N - 2 - 1) = 1;
			}

			if (j  - 1 == 0) {
				b(k - 1) -= rho_bound;
			}
			else {
				A.insert(k - 1, k - 1 - 1) = 1;
			}

			if ( j + 1 == N - 1) {
				b(k - 1) -= rho_bound;
			}
			else {
				A.insert(k - 1, k + 1 - 1) = 1;
			}
	}
	
	//cout << "A=" << endl;
	//for (int n = 0; n < (N - 2)*(N - 2); n++) 
	//	for (int m = 0; m < (N - 2)*(N - 2); m++) {
	//		cout << A.coeff(n, m) << "  ";
	//		if (m == (N - 2)*(N - 2) - 1) cout << "\n";
	//}

	//cout << "b=" << endl;
	//for (int k = 0; k < (N - 2)*(N - 2); k++) {
	//	cout << b(k) << "\n";
	//}

	VectorXd r((N - 2)*(N - 2));
	r = b - A*Phi;
	VectorXd d((N - 2)*(N - 2));
	d = r;

	//cout << "r=" << endl;
	//for (int k = 0; k < (N - 2)*(N - 2); k++) {
	//	cout << r(k) << "\n";
	//}
	//cout << "d=" << endl;
	//for (int k = 0; k < (N - 2)*(N - 2); k++) {
	//	cout << d(k) << "\n";
	//}
	double c, alpha, tempc, temp,tempalpha;
	while (r.dot(r)>threshold)
	{
		tempc = d.transpose()*A*d;
		c = 1. / tempc;
		tempalpha = d.dot(r);
		alpha = tempalpha*c;
		Phi = Phi + alpha*d;
		r = b - A*Phi;

		temp = r.transpose()*A*d;
		d = r - c*temp*d;

	}

	for (int i = 1; i < N - 1; i++)
		for (int j = 1; j < N - 1; j++) {
			int k = j + (i - 1)*(N - 2);
			phi(i, j) = Phi(k - 1);
	}

	string filename = "Gradiant" + to_string(N) + "x0y0" + to_string(x0) + to_string(y0) + ".txt";
	fstream myfile(filename, ios::out | ios::trunc);
	for (int n = 0; n < N; n++)
		for (int m = 0; m < N; m++) {
			myfile << setw(10);
			myfile << phi(n, m) << "  ";
			if (m == N - 1) myfile << "\n";
		}
	myfile.close();

	system("pause");
	return 0;
}
