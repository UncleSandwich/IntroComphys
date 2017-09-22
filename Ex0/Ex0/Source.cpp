#include<iostream>
#include<string>

using namespace std;

void Number();


int main() {
	cout << "Hello World!\n"; //print "Hello World"
	Number();//the program to print square of integer
	system("pause");
	return 0;
}

void Number() {
	int i;
	for (i = 1; i <= 10; i++) {
		cout << "i:" << i << "\t" << "i^2:" << i*i << "\n";
	}
}