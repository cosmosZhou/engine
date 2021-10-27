// as in the form x, y, z or x, y, z,
#pragma once
#include "MultiVariableOperator.h"
struct Comma : MultiVariableOperator
{
	__declare_common_interface(0, 0);

    string toString()
    {
        return implode(", ", array_map(fn ($node) => $node->toString(), $this->args));
    }
}
;
