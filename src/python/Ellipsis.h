#pragma once

#include "PyObject.h"

struct Ellipsis : PyObject
{
	__declare_common_interface(0, 0);
    Ellipsis(PyObject *parent);

    string toString();
};
