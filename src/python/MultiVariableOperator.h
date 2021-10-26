#pragma once
#include "PyObject.h"

struct MultiVariableOperator : PyObject
{

    MultiVariableOperator(vector<PyObject*> &args, PyObject *parent);

    vector<PyObject*> $args;

    void replace(PyObject *old, PyObject *$new);

    PyObject *append_comma(PyObject *child);

    ~MultiVariableOperator();
};

