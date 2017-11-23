#include<iostream>
#include<fstream>
#include<time.h>
#include<stdio.h>
#include<numeric>
#include <iomanip>
#include<string>

using namespace std;

#define L 300 // lattice size

double simple_random_walk(int, int);
double chains_of_particles(int, int);

int main() {
	int N_list[20]{ 0 }; //the list of different steps of one random walk, 100 is the smallest element
	int M_list[20]{ 0 }; //the list of different Monte Carlo steps of calculating average of R^2, 100 is the smallest element 

	for (int i = 0; i < 20; i++) {
		M_list[i] = 1000 + i * 1000;
		N_list[i] = 10 + i * 1;
	}

	int N = N_list[0], M = M_list[0];

	double delta_over_R2_SRW;
	double expected_R_square_SRW;
	double delta_over_R2_CP;
	double expected_R_square_CP;

	//task 1
	/*string filename = "N" + to_string(N) + "RSW.txt";
	fstream myfile(filename, ios::out | ios::trunc);
	for (int j = 0; j < 20; j++) {
		M = M_list[j];
		delta_over_R2_SRW = simple_random_walk(N, M);
		myfile << M << "  " << delta_over_R2_SRW << "\n";
	}
	myfile.close();*/
	/*M = 5000;
	string filename = "M" + to_string(M) + "RSW.txt";
	fstream myfile(filename, ios::out | ios::trunc);
	for (int j = 0; j < 20; j++) {
		N = N_list[j];
		expected_R_square_SRW = simple_random_walk(N, M);
		myfile << N << "  " << expected_R_square_SRW << "\n";
	}
	myfile.close();
	*/

	//task 2
	/*string filename = "N" + to_string(N) + "CP.txt";
	fstream myfile(filename, ios::out | ios::trunc);
	for (int j = 0; j < 20; j++) {
	M = M_list[j];
	delta_over_R2_CP = chains_of_particles(N, M);
	myfile << M << "  " << delta_over_R2_CP << "\n";
	}
	myfile.close();*/
	M = 5000;
	string filename = "M" + to_string(M) + "CP.txt";
	fstream myfile(filename, ios::out | ios::app);
	for (int j = 10; j < 20; j++) {
		N = N_list[j];
		expected_R_square_CP = chains_of_particles(N, M);
		myfile << N << "  " << expected_R_square_CP << "\n";
	}
	myfile.close();
	


	//system("pause");
	return 0;
}

double simple_random_walk(int N, int M) {
	int seed = time(NULL);
	srand(seed);


	int start_point_x = L / 2, start_point_y = L / 2;
	int *r_square = new int[M];
	double expected_R_square, expected_R_square_square;
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
		/*for (int k = 0; k < L; k++)
			for (int l = 0; l < L; l++) {
				if ((k*L + l) % L == 0) cout << "\n";
				cout << setw(3) << lattice[k*L + l] << " ";
			}
		cout << endl;
		system("pause");*/
		
	}
	int *r_square_square = new int[M];
	for (int j = 0; j < M; j++) r_square_square[j] = r_square[j] * r_square[j];
	expected_R_square = accumulate(r_square, r_square + M, 0.) / double(M);
	expected_R_square_square = accumulate(r_square_square, r_square_square + M, 0.) / double(M);
	double delta = sqrt((expected_R_square_square - expected_R_square*expected_R_square) / double(M));
	delete[] r_square, r_square_square;
	return expected_R_square;
}

double chains_of_particles(int N, int M) {
	int seed = time(NULL);
	srand(seed);

	int start_point_x = L / 2, start_point_y = L / 2, start_point_z = L / 2;
	int move_direction;
	int *r_square = new int[M];
	double expected_R_square, expected_R_square_square;

	for (int i = 0; i < M; i++) {
		int lattice[L*L*L]{ 0 };
		lattice[start_point_x + start_point_y*L + start_point_z*L*L] = 1;
		int x = start_point_x, y = start_point_y, z = start_point_z;
		int n = 0;
		int n_cout = 0;
		int n_temp;
		while(n<=N) {
			n_temp = n;
			n++;
			move_direction = rand() % 6;
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
				if (z != L - 1) {
					if (lattice[x + (y + 1)*L + z*L*L] != 1) {
						z++;  //move up
						lattice[x + y*L + z*L*L] = 1;
					}
					else n--;
				}
				else n--;
				break;
			case 3:
				if (z != 0){
					if (lattice[x + (y - 1)*L + z*L*L] != 1) {
						z--;  //move down
						lattice[x + y*L + z*L*L] = 1;
					}
					else n--;
				}
				else n--;
				break;
			case 4:
				if (x != L - 1 && y != L - 1 && z != L - 1) {
					if (lattice[x + (y + 1)*L + z*L*L] != 1) {
						y++;  //move deep
						lattice[x + y*L + z*L*L] = 1;
					}
					else n--;
				}
				else n--;
				break;
			case 5:
				if (x != 0 && y != 0 && z != 0) {
					if (lattice[x + (y - 1)*L + z*L*L] != 1) {
						y--;  //move sallow
						lattice[x + y*L + z*L*L] = 1;
					}
					else n--;
				}
				else n--;
				break;
			default:
				break;
			}
			//cout << n << "\n";
			if (n_temp == n) n_cout++;
			else n_cout = 0;
			if (n_cout > 50) {
				//cout << "Stuck\n";
				i--;
				//system("pause");
				break;
			}
		}
		r_square[i] = pow(x - start_point_x, 2) + pow(y - start_point_y, 2) + pow(z - start_point_z, 2);
	/*	for (int k = 0; k < L; k++)
			for (int l = 0; l < L; l++)
				for (int o = 0; o < L; o++)
				{
					if ((k*L + l) % L == 0) cout << "\n";
					cout << setw(3) << lattice[k*L + l] << " ";
				}
		cout << endl;*/
	}
	int *r_square_square = new int[M];
	for (int j = 0; j < M; j++) r_square_square[j] = r_square[j] * r_square[j];
	expected_R_square = accumulate(r_square, r_square + M, 0.) / double(M);
	expected_R_square_square = accumulate(r_square_square, r_square_square + M, 0.) / double(M);
	double delta = sqrt((expected_R_square_square - expected_R_square*expected_R_square) / double(M));
	delete[] r_square, r_square_square;
	return expected_R_square;
}