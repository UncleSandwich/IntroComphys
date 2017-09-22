#include<iostream>
#include<string>
#include<sstream>

using namespace std;

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
	cout << "Please enter the number of random numbers you want to generate:";
	string str;
	int i; //number of random number
	getline(cin, str);
	stringstream(str) >> i;
	cout << "Please enter the seed:";
	int seed;//initial value of random number
	getline(cin, str);
	stringstream(str) >> seed;

	RN_Congru rnseq;
	rnseq.seq = new int[i];
	rnseq.seq[0] = seed;
	for (int j = 1; j < i; j++) {
		rnseq.seq[j] = rnseq.Congru(&rnseq.seq[j]);
	}
	cout << "Random number sequence:(c=3, p=31)\n";
	for (int j = 0; j < i; j++) {
		cout << rnseq.seq[j] << " ";
	}
	cout << endl;

	
	cout << "Do you want to select c and p? (y/n):";
	getline(cin, str);
	if (str == "n") {
		system("pause");
		return 0;
	}
	else if (str == "y") {
		int a, b;
		cout << "c=";
		getline(cin, str);
		stringstream(str) >> a;
		cout << "p=";
		getline(cin, str);
		stringstream(str) >> b;

		RN_Congru rnseq2{ a,b };
		rnseq2.seq = new int[i];
		rnseq2.seq[0] = seed;
		for (int j = 1; j < i; j++) {
			rnseq2.seq[j] = rnseq2.Congru(&rnseq2.seq[j]);
		}
		printf("Random number sequence:(c=%i, p=%i)\n", a, b);
		for (int j = 0; j < i; j++) {
			cout << rnseq2.seq[j] << " ";
		}
		cout << endl;
	}
	else {
		cout << "You have enter invalid charater.\n";
	}

	system("pause");
	return 0;
}