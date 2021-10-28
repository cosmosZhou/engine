#pragma once
#include "BinaryOperator.h"
struct NotContains : BinaryOperator
{
	__declare_common_interface(0, 0);
	string $operator() {
		return "not in";
	}

    bool $in_is_received = false;

};
