#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include "GnuPlot.h"

using namespace std;

void task1(int, int);
void square_test(string filename);
void cube_test(string filename);
void diff_cp(int, int);
//void compare_rand_drand48(int, int);

void plot(string, string);


class RN_Congru {
	int c, p;
public:
	RN_Congru(int a, int b) :c(a), p(b) {};
	RN_Congru() {
		c = 3;
		p = 31;
	};
	int * seq;
	int Congru(int* arrayPointer) {return (c*(*(arrayPointer - 1))) % p;}

};

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

	string filename = "CongruRNG(c=3,p=31,number of numbers=" + to_string(i) \
		+ " seed=" + to_string(seed) + ".txt";
	fstream myfile(filename, ios::out | ios::trunc);

	if (myfile.is_open()) {
		cout << "Random number sequence:(c=3, p=31)\n";
		for (int j = 0; j < i; j++) {
			myfile << rnseq.seq[j] << "\n";
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

	
	//square test
	square_test(filename);

	//cube test
	cube_test(filename);

	//choose another c,p
	cout << "Please choose anoter c and p:\n";
	diff_cp(i, seed);

	//compare built-in rand() and drand48()
	//compare_rand_drand48(i, seed);
	
}

void square_test(string filename) {
	fstream myfile(filename, ios::in);
	plot(filename, filename.replace(filename.end() - 3, filename.end(), "png"));

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

	string filename = "CongruRNG(c=" + str1 + ",p=" + str2 + ", number of numbers = " + to_string(i) \
		+ " seed = " + to_string(seed) + ".txt";
	fstream myfile(filename, ios::out | ios::trunc);
	if (myfile.is_open()) {
		cout << "Random number sequence:(c=" << str1 << ", p=" << str2 << ")\n";
		for (int j = 0; j < i; j++) {
			myfile << rnseq2.seq[j] << "\n";
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

void plot(string filenameInput, string filenameOutput) {			     //This function plots the data contained in the txt file specified as filenameOutput

	Gnuplot plot;
	plot("set title \"Plot\"");
	plot("set size square");
	plot("set term png");
	plot("set output '" + filenameOutput + "'");
	plot("set grid ytics lt 0 lw 1 lc rgb \"#bbbbbb\"");
	plot("set grid xtics lt 0 lw 1 lc rgb \"#bbbbbb\"");
	plot("plot '" + filenameInput + "'");
	system("pause");

}