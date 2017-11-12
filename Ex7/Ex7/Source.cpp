#include<iostream>
#include<fstream>
#include<string>
#include"drand48.h"
#include"latticeview.h"
#include <time.h>
#include <stdio.h>
#include <iomanip>

#define N 20000 //the number of particles
#define L 500  //size of lattice

using namespace std;

int main() {
	int seed = time(NULL);
	srand(seed);
	int lattice[L*L]{ 0 };
	for (int j = 0; j < L; j++) {
		lattice[0*L + j] = -1;  //set the bottom line of lattice as the seed
	}
	int n = 0; //current number of particles
	int size_of_cluster = 0;
	int height_of_aggregation = 0;
	int generation_height = 2; //the height that a new particle generate from
	int max_height = generation_height * 2; //the height that regard the particle drifted away
	do {
		int y = rand() % L, x = generation_height; //paticle position in the lattice
		n++;
		//cout << n << "\n";
		bool has_reach_cluster = false;
		if (x >= L) break;
		do {
			if (max_height >= L) max_height = L-1;
			int move_direction = rand() % 4;
			switch (move_direction)
			{
			case 0:
				if (x != L - 1 && y != L - 1) y++;  //move right
				break;
			case 1:
				if (x != 0 && y != 0) y--;  //move left
				break;
			case 2:
				if (x != L - 1) x++;  //move up
				break;
			case 3:
				if (x != 0) x--;  //move down
				break;
			default:
				break;
			}
			if (x >= max_height) {
				//cout << "drifted away";
				n--;
				break;
			}
			if (lattice[x*L + y] == -1) {
				size_of_cluster++;
				lattice[x*L + y] = size_of_cluster;
				has_reach_cluster = true;
				if ((x + 3) > generation_height) {
					generation_height = x + 2;
					max_height = generation_height * 2;
				}
			}
			if (has_reach_cluster) {
				if (x != L - 1)
					if (lattice[(x + 1)*L + y] == 0) lattice[(x + 1)*L + y] = -1;
				if (x != 0)
					if (lattice[(x - 1)*L + y] == 0) lattice[(x - 1)*L + y] = -1;
				if (x != 0 && y != 0)
					if (lattice[x*L + (y - 1)] == 0) lattice[x*L + (y - 1)] = -1;
				if (x != L - 1 && y != L - 1)
					if (lattice[x*L + (y + 1)] == 0) lattice[x*L + (y + 1)] = -1;
			}
		} while (!has_reach_cluster);
		/*for (int i = 0; i < L; i++)
			for (int j = 0; j < L; j++) {
				if ((i*L + j) % L == 0) cout << "\n";
				cout << setw(3) << lattice[i*L + j] << " ";
			}
		cout << endl;*/
	} while (n < N);

	int image_width = 1000, image_height = 1000;
	Print_lattice(lattice, L, L, image_width, image_height, "output5.ppm");

	//system("pause");
	return 0;
}