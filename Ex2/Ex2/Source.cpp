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

#define N 100 //lattice size
#define ProbSetLength 10
#define ImageWidth 700  //image width
#define ImageHeight 700 //image height

using namespace std;

void task1(); // plot a square lattice
int task2(double); // double: probability of occupying a site, return: 0/1 for having a spanning cluster
void task3(); 



int main() {
	//task1
	//task1();

	////task2
	double p[ProbSetLength];
	int wheter_spanning[ProbSetLength];
	for (int i = 0; i < ProbSetLength; i++) {
		p[i] = drand48();
		cout << "p[" << i << "]=" << p[i] << "\n";
		wheter_spanning[i] = task2(p[i]);
	}

	for (int i = 0; i < ProbSetLength; i++) {
		cout << "whether spanning[" << i << "]:" << wheter_spanning[i] << "\n";
	}
	

	////task3
	//task3();

	system("pause");
	return 0;
}

void task1() {
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

int task2(double p) {
	int lat[N*N];
	char filename[50];
	//initialize lattice with occupied sites
	int K = rand();
	for (int k = 0; k < K; k++) drand48();
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			lat[i*N+j] = drand48() < p ? 1 : 0;
		}
			

	int shortest_time = 0;
	int life_time = 0;
	bool fire_alive = false;
	bool fire_arrived = false;
	//set fire at time=1 on the first row
	int time = 1;
	for (int j = 0; j < N; j++) lat[0 * N + j] = 2;
	/*sprintf(filename, "lattice N=%d p=%f initial.ppm", N, p);
	Print_lattice(lat, N, N, ImageWidth, ImageHeight, filename);*/
	// burning spread
	while (true)
	{
		if (fire_arrived == false)
			for (int j = 0; j < N; j++) 
				if (lat[(N - 1)*N + j] == 2) {
					shortest_time = time; //record the time that fire reaches the other side
					fire_arrived = true;
					sprintf(filename, "lattice N=%d p=%f shortest_time=%d.ppm", N, p, shortest_time);
					Print_lattice(lat, N, N, ImageWidth, ImageHeight, filename);
				}
					
		fire_alive = false;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				if (lat[i*N + j] == 2) {
					fire_alive = true;
					// spread the fire from burning tree to neighbouring green trees
					if (((i - 1)*N + j) >=  j) //check whether the site is on the periphery
						if (lat[(i - 1)*N + j] == 1) 
							lat[(i - 1)*N + j] = 4;
					if (((i + 1)*N + j) <= (N - 1)*N + j)
						if (lat[(i + 1)*N + j] == 1) 
							lat[(i + 1)*N + j] = 4;
					if ((i*N + (j - 1)) >= i*N)
						if (lat[i*N + (j - 1)] == 1) 
							lat[i*N + (j - 1)] = 4;
					if ((i*N + (j + 1)) <= i*N + N - 1)
						if (lat[i*N + (j + 1)] == 1) 
							lat[i*N + (j + 1)] = 4;
					//burning trees has burn out
					lat[i*N + j] = 3;
				}
			}
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				if (lat[i*N + j] == 4) 
					lat[i*N + j] = 2;
			}
		if (fire_alive == true) life_time++;
		else if (fire_alive == false) break;
		time++;
		/*sprintf(filename, "lattice N=%d p=%f time=%d.ppm", N, p, time);
		Print_lattice(lat, N, N, ImageWidth, ImageHeight, filename);*/
		if (time > N*N) {
			cout << "infinite time occurs!\n";
			break;
		}

	}
	cout << "shortest time=" << shortest_time << "\n";
	cout << "life_time=" << life_time << "\n";
	cout << endl;
	//sprintf(filename, "lattice N=%d p=%f.ppm", N, p[i]);
	//Print_lattice(lat, N, N, ImageWidth, ImageHeight, filename);
	if (fire_arrived) return 1;
	else if (!fire_arrived) return 0;
	else return -1;
	
}