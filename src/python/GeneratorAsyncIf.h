// as in the form: i async for i in (1, 2, 3) if i
#pragma once
#include "GeneratorAsync.h"
struct GeneratorAsyncIf: GeneratorAsync {
	__declare_common_interface(0, 0)

	PyObject *$cond;

	GeneratorAsyncIf(PyObject *expr, PyObject *var, PyObject *domain,
			PyObject *cond, PyObject *parent) :
			GeneratorAsync(expr, var, domain, parent), cond(cond) {
		cond->parent = this;
	}

	void replace(PyObject *old, PyObject *$new) {
		if (old == this->cond) {
			this->cond = $new;
		} else {
			GeneratorAsync::replace(old, $new);
		}
	}

	string toString() {
		return GeneratorAsync::toString() + " if " + this->cond->toString();
	}
}
;
