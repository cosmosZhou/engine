// as in the form x, y, z or x, y, z,
#pragma once
#include "MultiVariableOperator.h"
struct Comma: MultiVariableOperator {
	__declare_common_interface(0, 0)

	Comma(const vector<PyObject*> &args): MultiVariableOperator(args){
	}

	Comma(vector<PyObject*> &args): MultiVariableOperator(args){
	}

	string toString() {
		return join(", ", array_map(&PyObject::toString, this->args));
	}
};
