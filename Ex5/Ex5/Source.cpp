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

#define change_smapling_number false
#define PARTICLE_NUMBER 50  //number of particles
#define NUMBER_OF_NUMBER_OF_SAMPLE 1000

#define change_particle_number true
#define NUMBER_OF_PARTICLE_NUMBER 1000  //number of particles
#define NUMBER_OF_SAMPLE 100


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
	
	bool is_accepted = true;
	//Monte Carlo
	

	if (change_smapling_number) {
		
		string str = "len=" + to_string(CUBE_LENGTH) + " r=" + to_string(RADIUS) + " n=" \
			+ to_string(PARTICLE_NUMBER) + " N_M=" + to_string(NUMBER_OF_NUMBER_OF_SAMPLE) + ".txt";
		fstream myfile(str, ios::out | ios::trunc);
		int number_of_sample[NUMBER_OF_NUMBER_OF_SAMPLE];
		for (int i = 0; i < NUMBER_OF_NUMBER_OF_SAMPLE; i++) {
			number_of_sample[i] = 1 * (i + 2);
		}
		particle *p;
		p = new particle[PARTICLE_NUMBER];
		srand48(time(NULL));
		for (int t = 0; t < NUMBER_OF_NUMBER_OF_SAMPLE; t++) {
			double d_mean_mean = 0;
			for (int k = 0; k < number_of_sample[t]; k++) {
				//generate a configration
				for (int i = 0; i < PARTICLE_NUMBER; i++) {
					int n = 0;
					// propose a particle until it is accepted
					do {
						n++;
						double p_newx, p_newy, p_newz;

						p_newx = (CUBE_LENGTH - 1) * drand48();
						//srand48(time(NULL));
						p_newy = (CUBE_LENGTH - 1) * drand48();
						//srand48(time(NULL));
						p_newz = (CUBE_LENGTH - 1) * drand48();
						particle p_new{ p_newx, p_newy, p_newz };
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
		delete[] p;
	}

	if (change_particle_number) {
		string str = "len=" + to_string(CUBE_LENGTH) + " r=" + to_string(RADIUS) + " N_n=" \
			+ to_string(NUMBER_OF_PARTICLE_NUMBER) + " M=" + to_string(NUMBER_OF_SAMPLE) + ".txt";
		fstream myfile(str, ios::out | ios::trunc);
		int number_of_particle[NUMBER_OF_PARTICLE_NUMBER];
		for (int i = 0; i < NUMBER_OF_PARTICLE_NUMBER; i++) {
			number_of_particle[i] = 1 * (i + 2);
		}
		
		srand48(time(NULL));
		for (int t = 0; t < NUMBER_OF_PARTICLE_NUMBER; t++) {
			double d_mean_mean = 0;
			particle *p;
			p = new particle[number_of_particle[t]];
			for (int k = 0; k < NUMBER_OF_SAMPLE; k++) {
				//generate a configration
				for (int i = 0; i < number_of_particle[t]; i++) {
					int n = 0;
					// propose a particle until it is accepted
					do {
						n++;
						double p_newx, p_newy, p_newz;

						p_newx = (CUBE_LENGTH - 1) * drand48();
						//srand48(time(NULL));
						p_newy = (CUBE_LENGTH - 1) * drand48();
						//srand48(time(NULL));
						p_newz = (CUBE_LENGTH - 1) * drand48();
						particle p_new{ p_newx, p_newy, p_newz };
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
							volume *= number_of_particle[t];
							cout << "volume: " << volume << "\n";
							cout << "volume fraction: " << volume / pow(CUBE_LENGTH, 3) << "\n";
							system("pause");
							return 0;
						}
					} while (!is_accepted);
				}
				//calculate the mean of distance
				double d_mean = 0;
				for (int i = 0; i < number_of_particle[t]; i++) {
					for (int j = 0; j < i; j++) {
						d_mean += distance(p[j], p[i]);
					}
				}
				d_mean *= (2. / (number_of_particle[t]*(number_of_particle[t] - 1)));
				//cout << "d_mean: " << d_mean << "\n";
				d_mean_mean += d_mean;
			}
			d_mean_mean *= 1. / NUMBER_OF_SAMPLE;

			//cout << "number of sample: " << number_of_sample[t] << endl;
			//cout << "mean of d_mean: " << d_mean_mean << endl;
			myfile << number_of_particle[t] << "  " << d_mean_mean << "\n";
			delete[] p;
		}
		myfile.close();
	}
	

	//system("pause");
	return 0;
}