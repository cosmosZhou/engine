#pragma once
#include "PyObject.h"

struct BinaryOperator: PyObject {
	object<PyObject> lhs, rhs;
	BinaryOperator(PyObject *lhs, PyObject *rhs, PyObject *parent) :
			PyObject(parent), lhs(lhs), rhs(rhs) {
		lhs->parent = rhs->parent = this;
	}

	void replace(PyObject *old, PyObject *$new) {
		if (lhs == old) {
			lhs = $new;
		} else if (rhs == old) {
			rhs = $new;
		} else
			throw std::runtime_error(
					"void replace(TreeNode old, TreeNode replacement) throws Exception");
	}

	string toString() {
		ostringstream cout;
		cout << lhs << " " << $operator() << " " << rhs;
		return cout.str();
	}

	virtual string $operator() = 0;
};
