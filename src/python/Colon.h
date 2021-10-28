// as in the form start:stop:step, or as in the form {k:v, k1:v2}
#pragma once
#include "MultiVariableOperator.h"
struct Colon: MultiVariableOperator {
	__declare_common_interface(0, 0)

	PyObject* append_colon();

	string toString() {
		return join(":", array_map(&PyObject::toString, this->args));
	}

	PyObject* append_comma(PyObject *child) {
		return this->parent->append_comma(this);
	}
};
