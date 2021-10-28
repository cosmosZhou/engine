#pragma once
#include "MultiVariableOperator.h"
struct Literals : MultiVariableOperator
{
	__declare_common_interface(0, 0);

    string toString()
    {
        return implode(" ", array_map(fn ($node) => $node->toString(), $this->args));
    }

    function append_comma($child)
    {
        return $this->parent->append_comma($this);
    }
}


;
