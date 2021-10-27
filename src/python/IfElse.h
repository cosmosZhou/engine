// as in the form: expr if cond else other
#pragma once
#include "PyObject.h"

struct IfElse : PyObject
{
	__declare_common_interface(0, 0);

    // must be an identifier, or a list of identifiers
    PyObject *expr;
    PyObject *cond;
    PyObject *other;

    IfElse($expr, $cond, $other, $parent);

    void replace(PyObject *old, PyObject *$new);

    string toString();

    string type();
};
