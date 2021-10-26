#pragma once
#include "BitwiseAnd.h"

int BitwiseAnd::input_precedence() {
	return 12;
}

int BitwiseAnd::stack_precedence() {
	return 0;
}

string BitwiseAnd::toString() {
	return "$this->lhs & $this->rhs";
}


string BitwiseAnd::type() {
	return "BitwiseAnd";
}
