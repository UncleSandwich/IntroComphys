#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#define _USE_MATH_DEFINES // for C++  
#include "math.h" 
#include "drand48.h"
#include "latticeview.h"
#include <stdlib.h>
#include <stdio.h> // for sprintf()

#define ImageWidth 700  //image width
#define ImageHeight 700 //image height

using namespace std;

void task1(); // plot a square lattice
int task2(int*, double*); //int: system size, double: probability of occupying a site, return: 0/1 for having a spanning cluster
void task3(); 



int main() {
	//task1
	task1();

	////task2
	//int N[10];
	//double p[10];
	//for (int i = 0; i < 10; i++) {
	//	p[i] = drand48();
	//	cout << "p[" << i << "]=" << p[i] << "\n";
	//	N[i] = rand() % 10;
	//	cout << "N[" << i << "]=" << N[i] << "\n";
	//}
	//task2(N, p);

	////task3
	//task3();

	//system("pause");
	return 0;
}

void task1() {
	const int N = 100;
	double p;
	cout << "Please enter the probability of occupying a site (0-1):";
	string str;
	getline(cin, str);
	stringstream(str) >> p;
	int lat[N*N];
	for (int icounter = 0; icounter < N*N; icounter++)
		lat[icounter] = drand48() < p ? 3 : 0; //I have change the black into gray in latticeview.h
	char filename[50];
	sprintf(filename, "lattice N=%d p=%f.ppm", N, p);
	Print_lattice(lat, N, N, ImageWidth, ImageHeight, filename);
}