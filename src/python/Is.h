#pragma once
#include "BinaryOperator.h"
struct Is : BinaryOperator
{
	__declare_common_interface(0, 0);
	string $operator() {
		return "is";
	}
};
