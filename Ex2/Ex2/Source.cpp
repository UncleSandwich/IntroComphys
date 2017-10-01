#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<iomanip>
#define _USE_MATH_DEFINES // for C++  
#include "math.h" 
#include "drand48.h"
#include "latticeview.h"
#include <stdlib.h>
#include <stdio.h> // for sprintf()
#include <tuple>

#define N 500 //lattice size
#define ProbSetLength 100
#define ImageWidth 700  //image width
#define ImageHeight 700 //image height

using namespace std;

class Forest_fire {
public:
	double probability;
	int shortest_time;
	int life_time;
	int whether_spanning;
};

class Statistic {
public:
	double probability;
	double fraction_of_percolation;
	double averg_shortest_time = 0;
	double averg_life_time = 0;
};

void task1(); // plot a square lattice
tuple<int, int, int> task2(double, fstream&); // double: probability of occupying a site, return: 0/1 for having a spanning cluster
void task3(); 



int main() {
	//task1
	//task1();

	//task2
	//double p[ProbSetLength];
	//Forest_fire fire[ProbSetLength];

	////fstream myfile("Forest fire.txt", ios::out | ios::trunc);
	//int K = rand();
	//for (int i = 0; i < ProbSetLength; i++) {
	//	for (int k = 0; k < K; k++) drand48();
	//	p[i] = drand48();
	//	fire[i].probability = p[i];
	//	//myfile << "p[" << i << "]=" << p[i] << "\n";
	//	tie(fire[i].whether_spanning, fire[i].shortest_time, fire[i].life_time) = task2(p[i], myfile);
	//}

	/*for (int i = 0; i < ProbSetLength; i++) {
		myfile << "whether spanning[" << i << "]:" << wheter_spanning[i] << "\n";
	}
	
	myfile.close();*/

	//task3
	task3();

	//system("pause");
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

tuple<int, int, int> task2(double p, fstream& myfile) {
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
					/*sprintf(filename, "lattice N=%d p=%f shortest_time=%d.ppm", N, p, shortest_time);
					Print_lattice(lat, N, N, ImageWidth, ImageHeight, filename);*/
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
	/*myfile << "shortest time=" << shortest_time << "\n";
	myfile << "life_time=" << life_time << "\n";
	myfile << endl;*/
	//sprintf(filename, "lattice N=%d p=%f.ppm", N, p[i]);
	//Print_lattice(lat, N, N, ImageWidth, ImageHeight, filename);
	if (fire_arrived) return {1, shortest_time, life_time };
	else if (!fire_arrived) return { 0, shortest_time, life_time };
	else return {-1, -2, -3};
	
}

void task3() {
	double p[ProbSetLength];
	Statistic fire[ProbSetLength];
	int shorest_time, life_time;
	const int repeat_time = 1000;
	int whether_spanning, spanning_counter = 0;

	string filename = "Forest fire statistic N=" + to_string(N) + ".txt";
	fstream myfile(filename, ios::out | ios::trunc);
	for (int i = 0; i < ProbSetLength; i++) {
		p[i] = i*(1.0 / ProbSetLength);
		fire[i].probability = p[i];
		for (int j = 0; j < repeat_time; j++) {
			tie(whether_spanning, shorest_time, life_time) = task2(p[i], myfile);

			if (whether_spanning != -1)
				spanning_counter += whether_spanning;
			else if (whether_spanning == -1)
				cout << "task 2 has occured error.\n";
			else
				cout << "Unknown error occurs.\n";

			fire[i].averg_shortest_time += double(shorest_time);
			fire[i].averg_life_time += double(life_time);
		}
		fire[i].fraction_of_percolation = double(spanning_counter) / repeat_time;
		fire[i].averg_shortest_time /= repeat_time;
		fire[i].averg_life_time /= repeat_time;
	}

	myfile << fixed;
	myfile << setprecision(15);
	for (int i = 0; i < ProbSetLength; i++) {
		myfile << fire[i].probability << "  " << fire[i].fraction_of_percolation << "  " << fire[i].averg_shortest_time << "  " << fire[i].averg_life_time << "\n";
	}

	myfile.close();


}