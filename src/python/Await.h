#pragma once
#include "UnaryOperator.h"

struct Await: UnaryOperator {
	__declare_common_interface(0, 0)

	string toString() {
		ostringstream cout;
		cout << "await " << this->arg;
		return cout.str();
	}

};
