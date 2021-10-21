#pragma once

#include "PyObject.h"

struct Ellipsis : PyObject
{

    Ellipsis(PyObject *parent);

    static int input_precedence();

    static int stack_precedence();

    string toString();
};
