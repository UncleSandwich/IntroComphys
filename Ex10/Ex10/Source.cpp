#include<iostream>
#include<fstream>
#include<string>
#include<tuple>
#define _USE_MATH_DEFINES
#include"math.h"

using namespace std;

#define g 9.8
#define v0 40
#define dt 0.001

tuple<double, double> velocity_RK4(double, double, double, double);
tuple<double, double> position_Euler(double, double, double, double);

int main() {
	double gamma, alpha, vx, vz, x, z;
	double x_farest, alpha_max;
	

	//Task 1
	//string filename = "trajectory"+to_string(gamma)+"pi4.txt";
	//fstream myfile(filename, ios::out | ios::trunc);
	//alpha = M_PI_4;
	//vx = v0*cos(alpha), vz = v0*sin(alpha);
	//x = 0, z = 0;
	//gamma = 2.5;
	//int n = 0;
	//while (z>=0)
	//{
	//	myfile << n*dt << " " << x << " " << z << " " << vx << " " << vz << "\n";
	//	tie(vx, vz) = velocity_RK4(vx, vz, gamma, alpha);
	//	tie(x, z) = position_Euler(x, z, vx, vz);
	//	n++;
	//	//cout << "t= " << n*dt << " z=" << z << "\n";
	//	if (n > 100000) {
	//		cout << x << " " << z;
	//		cout << "\n too many steps\n";
	//		break;
	//	}
	//}
	//x_farest = x;
	////cout << "x_farest: " << x_farest << "\n";
	//myfile.close();

	//Task 2
	string filename = "alpha_max_over_gamma" + to_string(v0) + ".txt";
	fstream myfile(filename, ios::out | ios::trunc);
	for (gamma = 0; gamma <= 5; gamma += 0.01) {
		x_farest = 0;
		alpha_max = 0;
		for (alpha = 0; alpha <= M_PI_2; alpha += 0.001) {
			vx = v0*cos(alpha), vz = v0*sin(alpha);
			x = 0, z = 0;
			int n = 0;
			while (z >= 0)
			{
				tie(vx, vz) = velocity_RK4(vx, vz, gamma, alpha);
				tie(x, z) = position_Euler(x, z, vx, vz);
				n++;
				//cout << "t= " << n*dt << " z=" << z << "\n";
				if (n > 100000) {
					cout << x << " " << z;
					cout << "\n too many steps\n";
					system("pause");
					break;
				}
			}
			if (x > x_farest) {
				x_farest = x;
				alpha_max = alpha;
			}
		}
		myfile << gamma << " " << alpha_max << "\n";
	}
	myfile.close();

	//system("pause");
	return 0;
}

tuple<double, double> velocity_RK4(double vx, double vz, double gamma, double alpha) {
	double k1x, k1z, k2x, k2z, k3x, k3z, k4x, k4z, kx, kz;
	double vx_dt, vz_dt;
	k1x = -gamma*sqrt(pow(vx,2) + pow(vz,2))*vx;
	k1z = -g - gamma*sqrt(vx*vx + vz*vz)*vz;
	k2x = -gamma*sqrt(pow(vx + 0.5*dt*k1x, 2) + pow(vz + 0.5*dt*k1z, 2))*(vx + 0.5*dt*k1x);
	k2z = -g - gamma*sqrt(pow(vx + 0.5*dt*k1x, 2) + pow(vz + 0.5*dt*k1z, 2))*(vz + 0.5*dt*k1z);
	k3x = -gamma*sqrt(pow(vx + 0.5*dt*k2x, 2) + pow(vz + 0.5*dt*k2z, 2))*(vx + 0.5*dt*k2x);
	k3z = -g - gamma*sqrt(pow(vx + 0.5*dt*k2x, 2) + pow(vz + 0.5*dt*k2z, 2))*(vz + 0.5*dt*k2z);
	k4x = -gamma*sqrt(pow(vx + dt*k3x, 2) + pow(vz + dt*k3z, 2))*(vx + dt*k3x);
	k4z = -g - gamma*sqrt(pow(vx + dt*k3x, 2) + pow(vz + dt*k3z, 2))*(vz + dt*k3z);
	kx = (1. / 6)*(k1x + 2 * k2x + 2 * k3x + k4x);
	kz = (1. / 6)*(k1z + 2 * k2z + 2 * k3z + k4z);
	vx_dt = vx + dt*kx;
	vz_dt = vz + dt*kz;
	return { vx_dt, vz_dt };
}

tuple<double, double> position_Euler(double x, double z, double vx, double vz) {
	double x_dt, z_dt;
	x_dt = x + vx*dt;
	z_dt = z + vz*dt;
	return { x_dt,z_dt };
}