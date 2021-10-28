#pragma once
#include "MultiVariableOperator.h"

struct FunctionCall: MultiVariableOperator {
	__declare_common_interface(0, 0)

	PyObject *name;

	FunctionCall(PyObject *name, vector<PyObject*> $args, PyObject *parent) :
			MultiVariableOperator(args, parent), name(name) {
		name->parent = this;
	}

	PyObject* append_right_parenthesis() {
		return this;
	}

	string toString() {
		ostringstream cout;
		cout << name << "(" << join(", ", array_map(&PyObject::toString, args)) << ")";

		return cout.str();
	}

	void replace(PyObject *old, PyObject *$new) {
		if (old == this->name) {
			this->name = $new;
		} else {
			MultiVariableOperator::replace(old, $new);
		}
	}
};
