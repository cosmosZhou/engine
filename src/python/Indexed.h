#pragma once
#include "MultiVariableOperator.h"

struct Indexed: MultiVariableOperator {
	__declare_common_interface(0, 0)
	;

	PyObject *base;

	Indexed(PyObject *base, vector<PyObject*> &args, PyObject *parent) :
			MultiVariableOperator(args, parent), base(base) {
		base->parent = this;
	}

	PyObject* append_right_bracket() {
		return this;
	}

	string toString() {
		ostringstream cout;
		cout << this->base << "["
				<< join(", ", array_map(&PyObject::toString, this->args))
				<< ']';
		return cout.str();
	}

	void replace(PyObject *old, PyObject *$new) {
		if (old == this->base) {
			this->base = $new;
		} else {
			MultiVariableOperator::replace(old, $new);
		}
	}
}
;
