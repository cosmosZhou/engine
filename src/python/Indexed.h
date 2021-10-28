#pragma once
#include "MultiVariableOperator.h"

struct Indexed : MultiVariableOperator
{
	__declare_common_interface(0, 0);

    PyObject *base;

    Indexed(PyObject *base, vector<PyObject*> &args, PyObject *parent): MultiVariableOperator(args, parent), base(base)
    {
        base->parent = this;
    }

    PyObject *append_right_bracket()
    {
        return this;
    }

    string toString()
    {
        return "$this->base[" . implode(", ", array_map(fn ($obj) => $obj->toString(), $this->args)) . ']';
    }

    void replace(PyObject *old, PyObject *$new)
    {
        if ($old === $this->base) {
            $this->base = $new;
        } else {
            parent::replace($old, $new);
        }
    }
}
;
