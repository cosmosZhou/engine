#pragma once
#include "MultiVariableOperator.h"
struct Literals: MultiVariableOperator {
	__declare_common_interface(0, 0)
	;

	string toString() {
		return join(" ", array_map(&PyObject::toString, this->args));
	}

	PyObject* append_comma(PyObject *child) {
		return this->parent->append_comma(this);
	}

};
