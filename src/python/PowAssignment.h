#pragma once
#include "BinaryOperator.h"
struct PowAssignment : BinaryOperator
{
	__declare_common_interface(10, 0);
	string $operator() {
		return "**=";
	}
};
