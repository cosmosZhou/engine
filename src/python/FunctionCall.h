#pragma once
#include "MultiVariableOperator.h"

struct FunctionCall : MultiVariableOperator
{

    int input_precedence();
    int stack_precedence();

    string name;

    FunctionCall(PyObject *name, vector<PyObject*> $args, PyObject*parent)
    {
        parent::__construct($args, $parent);
        $this->name = $name;
        $name->parent = $this;
    }

    function append_right_parenthesis()
    {
        return $this;
    }

    function toString()
    {
        return "$this->name(" . implode(", ", array_map(fn ($obj) => $obj->toString(), $this->args)) . ')';
    }

    function replace($old, $new)
    {
        if ($old === $this->name) {
            $this->name = $new;
        } else {
            parent::replace($old, $new);
        }
    }
}
;
