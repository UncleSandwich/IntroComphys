#include<iostream>
#include<fstream>
#include<time.h>
#include<stdio.h>
#include<numeric>
#include <iomanip>

using namespace std;

#define L 20 // lattice size

double simple_random_walk(int, int);
double chains_of_particles(int, int);

int main() {
	int N_list[20]{ 100 }; //the list of different steps of one random walk, 100 is the smallest element
	int M_list[20]{ 100 }; //the list of different Monte Carlo steps of calculating average of R^2, 100 is the smallest element 

	int N = N_list[0], M = M_list[0];

	double expected_R_square_SRW;
	double expected_R_square_CP;

	//task 1
	//expected_R_square_SRW = simple_random_walk(N, M);

	//task 2
	expected_R_square_CP = chains_of_particles(N, M);


	system("pause");
	return 0;
}

double simple_random_walk(int N, int M) {
	int seed = time(NULL);
	srand(seed);


	int start_point_x = L / 2, start_point_y = L / 2;
	int *r_square = new int[M];
	double expected_R_square;
	int move_direction;

	for (int i = 0; i < M; i++) {
		int lattice[L*L]{ 0 };
		lattice[start_point_x + start_point_y*L] = 1;
		int x = start_point_x, y = start_point_y;
		for (int j = 0; j < N; j++) {
			move_direction = rand() % 4;
			switch (move_direction)
			{
			case 0:
				if (x != L - 1 && y != L - 1) x++;  //move right
				else j--;
				break;
			case 1:
				if (x != 0 && y != 0) x--;  //move left
				else j--;
				break;
			case 2:
				if (y != L - 1) y++;  //move up
				else j--;
				break;
			case 3:
				if (y != 0) y--;  //move down
				else j--;
				break;
			default:
				break;
			}
			lattice[x + y*L] = 1;
			
		}
		r_square[i] = pow(x - start_point_x, 2) + pow(y - start_point_y, 2);
		for (int k = 0; k < L; k++)
			for (int l = 0; l < L; l++) {
				if ((k*L + l) % L == 0) cout << "\n";
				cout << setw(3) << lattice[k*L + l] << " ";
			}
		cout << endl;
		system("pause");
		
	}
	expected_R_square = accumulate(r_square, r_square + M, 0.) / double(M);
	delete[] r_square;
	return expected_R_square;
}

double chains_of_particles(int N, int M) {
	int seed = time(NULL);
	srand(seed);

	int start_point_x = L / 2, start_point_y = L / 2, start_point_z = L / 2;
	int move_direction;
	int *r_square = new int[M];
	double expected_R_square;

	for (int i = 0; i < M; i++) {
		int lattice[L*L*L]{ 0 };
		lattice[start_point_x + start_point_y*L + start_point_z*L*L] = 1;
		int x = start_point_x, y = start_point_y, z = start_point_z;
		int n = 0;
		while(n<=N) {
			n++;
			move_direction = rand() % 8;
			switch (move_direction)
			{
			case 0:
				if (x != L - 1 && y != L - 1 && z != L - 1){
					if (lattice[(x + 1) + y*L + z*L*L] != 1) {
						x++;  //move right
						lattice[x + y*L + z*L*L] = 1;
					}
					else n--;
				}
				else n--;
				break;
			case 1:
				if (x != 0 && y != 0 && z != 0) {
					if (lattice[(x - 1) + y*L + z*L*L] != 1) {
						x--;  //move left
						lattice[x + y*L + z*L*L] = 1;
					}
					else n--;
				}
				else n--;
				break;
			case 2:
				if (y != L - 1) {
					if (lattice[x + (y + 1)*L] != 1) {
						y++;  //move up
						lattice[x + y*L] = 1;
					}
					else n--;
				}
				else n--;
				break;
			case 3:
				if (y != 0){
					if (lattice[x + (y - 1)*L] != 1) {
						y--;  //move down
						lattice[x + y*L] = 1;
					}
					else n--;
				}
				else n--;
				break;
			default:
				break;
			}
		}
		r_square[i] = pow(x - start_point_x, 2) + pow(y - start_point_y, 2);
		for (int k = 0; k < L; k++)
			for (int l = 0; l < L; l++) {
				if ((k*L + l) % L == 0) cout << "\n";
				cout << setw(3) << lattice[k*L + l] << " ";
			}
		cout << endl;
	}
	expected_R_square = accumulate(r_square, r_square + M, 0.) / double(M);
	delete[] r_square;
	return expected_R_square;
}