#pragma once

#include "BinaryOperator.h"

struct AddAssignment : BinaryOperator
{
	__declare_common_interface(10, 0)

	string toString() {
		ostringstream cout;
		cout << lhs << " += " << rhs;
		return cout.str();
	}

};
