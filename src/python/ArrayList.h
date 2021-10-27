#pragma once

#include "MultiVariableOperator.h"
// as in the form [x, y, z] or [x, y, z, ] or [x,]
struct ArrayList : MultiVariableOperator
{
	__declare_common_interface(0, 0)

	string toString() {
		ostringstream cout;
		auto arr = array_map([] (PyObject *node) { return node->toString();}, this->args);

		cout << "[" << join(arr, ", ") << "]";
		return cout.str();
	}

    PyObject *append_right_bracket()
    {
        return this;
    }
};
