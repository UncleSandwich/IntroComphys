#include<iostream>
#include<fstream>
#include<string>
#include<stdio.h>      /* printf, NULL */
#include<stdlib.h>     /* srand, rand */
#include<time.h>       /* time */
#include"drand48.h"
#define _USE_MATH_DEFINES
#include"math.h"

#define CUBE_LENGTH 3001  //the size of cube containing particles
#define RADIUS 1  //radius of the sphere particle
#define PARTICLE_NUMBER 100  //number of particles
#define NUMBER_OF_NUMBER_OF_SAMPLE 100

using namespace std;

class particle
{
public:
	double x, y, z;
	particle(double px, double py, double pz) { x = px; y = py; z = pz; }
	particle() {};
};

double distance(particle p1, particle p2) {
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
}


int main() {
	double volume = 4. / 3. * M_PI * pow(RADIUS, 3);
	particle *p;
	p = new particle[PARTICLE_NUMBER];
	bool is_accepted = true;
	//Monte Carlo
	string str = "len=" + to_string(CUBE_LENGTH) + " r=" + to_string(RADIUS) + " n=" + to_string(PARTICLE_NUMBER) + ".txt";
	fstream myfile(str, ios::out | ios::trunc);
	int number_of_sample[NUMBER_OF_NUMBER_OF_SAMPLE];
	for (int i = 0; i < NUMBER_OF_NUMBER_OF_SAMPLE; i++) {
		number_of_sample[i] =  10 * (i + 2);
	}
	for (int t = 0; t < NUMBER_OF_NUMBER_OF_SAMPLE; t++) {
		double d_mean_mean = 0;
		for (int k = 0; k < number_of_sample[t]; k++) {
			//generate a configration
			for (int i = 0; i < PARTICLE_NUMBER; i++) {
				int n = 0;
				do {
					n++;
					srand48(time(NULL));
					particle p_new{ (CUBE_LENGTH - 1) * drand48(), (CUBE_LENGTH - 1) * drand48(), (CUBE_LENGTH - 1) * drand48() };
					//cout << "p_new.x: " << p_new.x << " p_new.y: " << p_new.y << " p_new.z: " << p_new.z << "\n";
					is_accepted = true;
					for (int j = 0; j < i; j++) {
						if (distance(p_new, p[j]) < 2 * RADIUS) {
							is_accepted = false;
							break;
						}
					}
					if (is_accepted) {
						p[i] = p_new;
					}
					if (n > 100) {
						cout << "Cant place more particle\n";
						volume *= PARTICLE_NUMBER;
						cout << "volume: " << volume << "\n";
						cout << "volume fraction: " << volume / pow(CUBE_LENGTH, 3) << "\n";
						system("pause");
						return 0;
					}
				} while (!is_accepted);
			}
			//calculate the mean of distance
			double d_mean = 0;
			for (int i = 0; i < PARTICLE_NUMBER; i++) {
				for (int j = 0; j < i; j++) {
					d_mean += distance(p[j], p[i]);
				}
			}
			d_mean *= (2. / (PARTICLE_NUMBER*(PARTICLE_NUMBER - 1)));
			//cout << "d_mean: " << d_mean << "\n";
			d_mean_mean += d_mean;
		}
		d_mean_mean *= 1. / number_of_sample[t];

		//cout << "number of sample: " << number_of_sample[t] << endl;
		//cout << "mean of d_mean: " << d_mean_mean << endl;
		myfile << number_of_sample[t] << "  " << d_mean_mean << "\n";
	}
	myfile.close();

	//system("pause");
	return 0;
}