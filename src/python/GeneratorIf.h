#pragma once
// as in the form: i for i in (1, 2, 3) if i

#include "Generator.h"
struct GeneratorIf: Generator {
	__declare_common_interface(0, 0);

	PyObject *cond;

	GeneratorIf(PyObject *expr, PyObject *var, PyObject *domain, PyObject *cond,
			PyObject *parent) :
			Generator(expr, var, domain, parent), cond(cond) {
		cond->parent = this;
	}

	void replace(PyObject *old, PyObject *$new) {
		if (old == this->cond) {
			this->cond = $new;
		} else {
			Generator::replace(old, $new);
		}
	}
	string toString() {
		ostringstream cout;
		cout << Generator::toString() << " if "<< this->cond;
		return cout.str();
	}
};
