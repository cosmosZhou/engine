#pragma once

#include "MultiVariableOperator.h"
// as in the form [x, y, z] or [x, y, z, ] or [x,]
struct ArrayList: MultiVariableOperator {
	__declare_common_interface(0, 0)
	ArrayList(vector<PyObject*> &args): MultiVariableOperator(args){

	}

	string toString() {
		ostringstream cout;
		cout << "[" << join(", ", array_map(&PyObject::toString, this->args))
				<< "]";
		return cout.str();
	}

	PyObject* append_right_bracket() {
		return this;
	}
};
