#pragma once
#include "UnaryOperator.h"
struct DoubleStar : UnaryOperator
{
	__declare_common_interface(0, 0);

	string $operator() {
		return "**";
	}
};
