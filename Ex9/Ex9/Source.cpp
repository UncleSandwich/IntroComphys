#include<iostream>
#include<string>
#include<fstream>

using namespace std;

#define use_secant true
#define x0 1
#define y0 1

double fx(double, double);
double fy(double, double);

int main() {
	double x = 1.35, y = 1.35;  //(|x_init-x| and |y_init-y| should not exceed Newton: 0.7, Secant: 0.35 )
	
	if (!use_secant) {
		string filename = "Newton11.txt";
		fstream myfile(filename, ios::out | ios::trunc);
		double J_f_x_n = (-x + x0) / (-1 + 2 * x*x + 2 * y*y + 2 * x0*(-2 * x + x0) + 2 * y0*(-2 * y*y0));
		double J_f_y_n = (-y + y0) / (-1 + 2 * x*x + 2 * y*y + 2 * x0*(-2 * x + x0) + 2 * y0*(-2 * y*y0));
		int n = 0;
		while (abs(x - x0)>0.000000000001 || abs(y - y0)>0.000000000001)
		{
			n++;
			myfile << x << "  " << y << "\n";
			x = x - J_f_x_n;
			y = y - J_f_y_n;
			J_f_x_n = (-x + x0) / (-1 + 2 * x*x + 2 * y*y + 2 * x0*(-2 * x + x0) + 2 * y0*(-2 * y*y0));
			J_f_y_n = (-y + y0) / (-1 + 2 * x*x + 2 * y*y + 2 * x0*(-2 * x + x0) + 2 * y0*(-2 * y*y0));
			if (n > 10000) break;
		}
		myfile.close();
	}
	else
	{
		string filename = "Secant11.txt";
		fstream myfile(filename, ios::out | ios::trunc);
		double F, Jxx, Jxy, Jyx, Jyy, hx, hy;
		double x_temp, y_temp;
		int n = 0;
		while (abs(x - x0) > 0.000000000001 || abs(y - y0) > 0.000000000001)
		{
			n++;
			//F = exp(-pow(x - x0, 2) - pow(y - y0, 2));
			myfile << x << "  " << y << "\n";
			hx = x*0.00000001;
			hy = y*0.00000001;
			Jxx = (fx(x + hx, y) - fx(x, y)) / hx;
			Jxy = (fx(x, y + hy) - fx(x, y)) / hy;
			Jyx = (fy(x + hx, y) - fy(x, y)) / hx;
			Jyy = (fy(x, y + hy) - fy(x, y)) / hy;
			x_temp = x - (1. / (Jxx*Jyy - Jxy*Jyx))*(Jyy*fx(x, y) - Jxy*fy(x, y));
			y_temp = y - (1. / (Jxx*Jyy - Jxy*Jyx))*(-Jyx*fx(x, y) + Jxx*fy(x, y));
			x = x_temp;
			y = y_temp;
			if (n > 10000) break;
		}
		myfile.close();
	}
	
	


	//system("pause");
	return 0;
}

double fx(double x, double y) {
	return -2*(x - x0)*exp(-pow(x - x0, 2) - pow(y - y0, 2));
}

double fy(double x, double y) {
	return -2*(y - y0)*exp(-pow(x - x0, 2) - pow(y - y0, 2));
}