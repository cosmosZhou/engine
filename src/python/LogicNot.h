#pragma once
#include "UnaryOperator.h"
struct LogicNot : UnaryOperator
{
	__declare_common_interface(0, 0);
	string $operator() {
		return "not ";
	}
};
