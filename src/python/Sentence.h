#pragma once
#include "PyObject.h"

struct Sentence: PyObject {
	__declare_common_interface(0, 0)

	Sentence(vector<PyObject*> &args) :
			args(args) {
		for (auto arg : args) {
			arg->parent = this;
		}
	}

	PyObject* append_left_brace();

	PyObject* append_left_parenthesis();

	PyObject* append_identifier(const string &name);

	vector<PyObject*> args;

	string toString() {
		return join("; ", array_map(&PyObject::toString, this->args));
	}

	void replace(PyObject *old, PyObject *$new) {
		auto i = indexOf(this->args, old);
		if (i == -1)
			throw std::runtime_error(
					"void replace(TreeNode old, TreeNode replacement) throws Exception");
		this->args[i] = $new;
	}

	PyObject* append_comma(PyObject *child);

	PyObject* append_semicolon(PyObject *child);

};
