#pragma once
#include "MultiVariableOperator.h"
struct Set: MultiVariableOperator {
	__declare_common_interface(0, 0)

	Set(const vector<PyObject*> &args) :
			MultiVariableOperator(args) {
	}

	string toString() {
		ostringstream cout;
		cout << "{" << join(", ", array_map(&PyObject::toString, this->args))
				<< "}";
		return cout.str();
	}

	PyObject* append_right_brace() {
		return this;
	}

};
