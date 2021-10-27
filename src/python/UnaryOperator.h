#pragma once
#include "PyObject.h"

struct UnaryOperator : PyObject
{
	__declare_common_interface(0, 0);

    UnaryOperator(PyObject *arg, PyObject *parent): PyObject(parent), arg(arg)
    {
        arg->parent = this;
    }

    object<PyObject> arg;

    void replace(PyObject *old, PyObject *$new)
    {
        if (this->arg == old) {
            this->arg = $new;
        } else
            throw new exception("void replace(TreeNode old, TreeNode replacement) throws Exception");
    }
}
;
