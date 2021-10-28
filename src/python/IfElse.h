// as in the form: expr if cond else other
#pragma once
#include "PyObject.h"

struct IfElse: PyObject {
	__declare_common_interface(0, 0)

	// must be an identifier, or a list of identifiers
	PyObject *expr;
	PyObject *cond;
	PyObject *other;

	IfElse(PyObject *expr, PyObject *cond, PyObject *other, PyObject *parent) :
			PyObject(parent), expr(expr), cond(cond), other(other) {
		cond->parent = this;
		expr->parent = this;
		other->parent = this;
	}

	void replace(PyObject *old, PyObject *$new) {
		if (old == this->expr) {
			this->expr = $new;
		} else if (old == this->cond) {
			this->cond = $new;
		} else if (old == this->other) {
			this->other = $new;
		} else
			throw std::runtime_error(
					"void replace(TreeNode old, TreeNode replacement) throws Exception");
	}

	string toString() {
		ostringstream cout;
		cout << this->expr  << " if " << this->cond << " else " << this->other;
		return cout.str();
	}

};
