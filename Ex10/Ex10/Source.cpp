#include<iostream>
#include<fstream>
#include<string>
#include<tuple>

using namespace std;

#define g 9.8
#define v0 40
#define dt 0.1

tuple<double, double> velocity_RK4(double, double, double, double);
tuple<double, double> position_Euler(double, double, double, double);

int main() {
	double gamma, alpha, vx, vz, x, z;
	double x_farest;

	vx = v0*cos(alpha), vz = v0*sin(alpha);
	x = 0, z = 0;
	gamma = 0.25;

	int n = 0;
	while (z>0)
	{
		tie(vx, vz) = velocity_RK4(vx, vz, gamma, alpha);
		tie(x, z) = position_Euler(x, z, vx, vz);
		n++;
		if (n > 10000) {
			cout << x << " " << z;
			cout << "\n too many steps\n";
			break;
		}
	}
	x_farest = x;
	cout << "x_farest: " << x_farest << "\n";

	system("pause");
	return 0;
}

tuple<double, double> velocity_RK4(double vx, double vz, double gamma, double alpha) {
	double vx_temp, vz_temp;



	return { vx, vz };
}

tuple<double, double> position_Euler(double x, double z, double vx, double vz) {
	x += vx*dt;
	z += vz*dt;
	return { x,z };
}