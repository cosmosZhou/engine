// as in the form (x, y, z) or (x, y, z, ) or (x, )
#pragma once
#include "MultiVariableOperator.h"
struct Tuple : MultiVariableOperator
{
	__declare_common_interface(0, 0);

    string toString()
    {
        return "(" . implode(", ", array_map(fn ($node) => $node->toString(), $this->args)) . ")";
    }

    function append_right_parenthesis()
    {
        return $this;
    }
}
;
