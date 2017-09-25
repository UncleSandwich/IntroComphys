#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#define _USE_MATH_DEFINES // for C++  
#include "math.h" 

using namespace std;

class RN_Congru {
public:	
	int c, p;
	RN_Congru(int a, int b) :c(a), p(b) {};
	RN_Congru() {
		c = 3;
		p = 31;
	};
	int * seq;
	int Congru(int* arrayPointer) {return (c*(*(arrayPointer - 1))) % p;}

};

void task1(int, int);
	void square_test(RN_Congru, int, int);
	void cube_test(RN_Congru, int, int);
	void diff_cp(int, int);
	//void compare_rand_drand48(int, int);
void task2(int, int);




int main(){

	cout << "This is Congruential RNG.\n";
	string str;
	cout << "Please enter the number of random numbers you want to generate:";
	int i;                           //number of random number
	getline(cin, str);
	stringstream(str) >> i;

	cout << "Please enter the seed:";
	int seed;                       //initial value of random number
	getline(cin, str);
	stringstream(str) >> seed;

	//task1
	task1(i, seed);
	

	system("pause");
	return 0;
}

void task1(int i, int seed) {
	RN_Congru rnseq;
	rnseq.seq = new int[i];
	rnseq.seq[0] = seed;
	for (int j = 1; j < i; j++) {
		rnseq.seq[j] = rnseq.Congru(&rnseq.seq[j]);
	}

	//square test
	square_test(rnseq, i, seed);

	//cube test
	cube_test(rnseq, i, seed);

	//choose another c,p
	cout << "do you want to change c and p? (y/n): ";
	string str;
	getline(cin, str);
	if (str == "y") {
		cout << "Please choose anoter c and p:\n";
		diff_cp(i, seed);
	}

	//compare built-in rand() and drand48()
	//compare_rand_drand48(i, seed);
	
}

void square_test(RN_Congru rnseq, int i, int seed) {
	string filename = "CongruRN_square_test(c=" + to_string(rnseq.c) + ",p=" + to_string(rnseq.p) \
		+ ",number of numbers=" + to_string(i) + " seed=" + to_string(seed) + ".dat";
	fstream myfile(filename, ios::out | ios::trunc);

	if (myfile.is_open()) {
		cout << "Generate square test datasheet on random number sequence:(c=" \
			+ to_string(rnseq.c) + ", p=" + to_string(rnseq.p) + ")\n";
		for (int j = 0; j < i - 1; j++) {
			myfile << rnseq.seq[j] << " " << rnseq.seq[j + 1] << "\n";
		}
		if (myfile.good()) {
			cout << "File is successfully written.\n";
		}
		else {
			cout << "Writting is fail.\n";
			myfile.clear();
		}
	}
	else {
		cout << "File is unable to open.\n";
	}
	myfile.close();

}

void cube_test(RN_Congru rnseq, int i, int seed) {
	string filename = "CongruRN_cube_test(c=" + to_string(rnseq.c) + ",p=" + to_string(rnseq.p) \
		+ ",number of numbers=" + to_string(i) + " seed=" + to_string(seed) + ".dat";
	fstream myfile(filename, ios::out | ios::trunc);

	if (myfile.is_open()) {
		cout << "Generate cube test datasheet on random number sequence:(c=" \
			+ to_string(rnseq.c) + ", p=" + to_string(rnseq.p) + ")\n";
		for (int j = 0; j < i - 2; j++) {
			myfile << rnseq.seq[j] << " " << rnseq.seq[j + 1] << " " << rnseq.seq[j+2] << "\n";
		}
		if (myfile.good()) {
			cout << "File is successfully written.\n";
		}
		else {
			cout << "Writting is fail.\n";
			myfile.clear();
		}
	}
	else {
		cout << "File is unable to open.\n";
	}
	myfile.close();
}

void diff_cp(int i, int seed) {
	int a, b;
	string str1, str2;
	cout << "c=";
	getline(cin, str1);
	stringstream(str1) >> a;
	cout << "p=";
	getline(cin, str2);
	stringstream(str2) >> b;

	RN_Congru rnseq2{ a,b };
	rnseq2.seq = new int[i];
	rnseq2.seq[0] = seed;
	for (int j = 1; j < i; j++) {
		rnseq2.seq[j] = rnseq2.Congru(&rnseq2.seq[j]);
	}

	square_test(rnseq2, i, seed);
	cube_test(rnseq2, i, seed);
	
}

void task2(int i, int seed) {
	int a = 16807, b = 2147483647;
	RN_Congru rn_for_phi{ a,b }, rn_for_radius{ a,b };
	rn_for_phi.seq = new int[i];
	rn_for_radius.seq = new int[i];
	rn_for_phi.seq[0] = seed;
	rn_for_radius.seq[0] = (seed + rand()) % b;

	for (int j = 1; j < i; j++) {
		rn_for_phi.seq[j] = rn_for_phi.Congru(&rn_for_phi.seq[j]);
		rn_for_radius.seq[j] = rn_for_radius.Congru(&rn_for_radius.seq[j]);
	}

	double * phi, *radius;
	phi = new double[i];
	radius = new double[i];
	for (int j = 0; j < i; j++) {
		phi[j] = rn_for_phi.seq[j] * 2 * M_PI;
		radius[j] = sqrt(2 * rn_for_radius.seq[j]);
	}

}