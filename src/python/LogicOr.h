#pragma once
#include "BinaryOperator.h"
struct LogicOr : BinaryOperator
{
	__declare_common_interface(0, 0);
	string $operator() {
		return "or";
	}
};
