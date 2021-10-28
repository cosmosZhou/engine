// as in the form: i async for i in (1, 2, 3)
#pragma once
#include "Generator.h"
struct GeneratorAsync: Generator {
	__declare_common_interface(0, 0)

	GeneratorAsync(PyObject *expr, PyObject *var, PyObject *domain,
			PyObject *parent) :
			Generator(expr, var, domain, parent) {
	}

	string toString() {
		return this->expr->toString() + " async for " + this->var->toString()
				+ " in " + this->domain->toString();
	}

};
