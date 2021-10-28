#pragma once
#include "PyObject.h"
struct Literal: PyObject {
	__declare_common_interface(0, 11)

	string literal;

	Literal(const string &literal, PyObject *parent = nullptr) :
			PyObject(parent), literal(literal) {
	}

	string toString() {
		return literal;
	}

	static bool is_literal_prefix(const string &literal) {
		static set<string> dict = { "r", "f", "u", "b", "R", "F", "U", "B",

		"rf", "rb", "rF", "rB", "Rf", "Rb", "RF", "RB", "fr", "br", "Fr", "Br",
				"fR", "bR", "FR", "BR" };
		return dict.count(literal);
	}

	PyObject *append_literal(string &infix, int &i, char mark);
};
