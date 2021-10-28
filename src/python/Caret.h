#pragma once
#include "PyObject.h"

struct Caret: PyObject {
	__declare_common_interface(0, 0)

	Caret(PyObject *parent = 0);

	PyObject* append_ellipsis();

	PyObject* append_literal(const string &infix, int &i, char mark);

	PyObject* append_digit(string &infix, int &i);

	PyObject* append_left_brace();

	bool is_Caret(){
		return true;
	}

	PyObject* append_left_parenthesis();

	PyObject* append_identifier(const string &name);

	string toString();

	PyObject* append_left_bracket();
};
