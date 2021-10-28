#pragma once
#include "BinaryOperator.h"
struct Sub : BinaryOperator
{
	__declare_common_interface(10, 0);
	string $operator() {
		return "-";
	}
};
