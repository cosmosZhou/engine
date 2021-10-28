#pragma once
#include "BinaryOperator.h"
struct Dot : BinaryOperator
{
	__declare_common_interface(10, 20);

	string toString() {
		ostringstream cout;
		cout << lhs << "." << rhs;
		return cout.str();
	}
};
