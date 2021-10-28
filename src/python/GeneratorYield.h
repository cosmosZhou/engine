// as in the form: return (yield x)
#pragma once
#include "UnaryOperator.h"
struct GeneratorYield : UnaryOperator
{
	__declare_common_interface(0, 0);

	string $operator() {
		return "yield ";
	}
};
