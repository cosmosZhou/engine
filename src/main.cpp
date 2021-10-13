#include <time.h>
#include <string>
#include <iostream>
using namespace std;

#include <stdio.h>

#include<iostream>

int main(int argc, char **argv) {
	cout << "argc = " << argc << endl;
	for (int i = 0; i < argc; ++i) {
		cout << argv[i] << endl;
	}

	return 0;
}
