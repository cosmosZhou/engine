// as in the form start:stop:step, or as in the form {k:v, k1:v2}
#pragma once
#include "MultiVariableOperator.h"
struct Colon : MultiVariableOperator
{
	__declare_common_interface(0, 0);

    function append_colon($self)
    {
        $caret = new Caret($this);
        $this->args[] = $caret;
        return $caret;
    }

    string toString()
    {
        return implode(":", array_map(fn ($node) => $node->toString(), $this->args));
    }

    function append_comma($child)
    {
        return $this->parent->append_comma($this);
    }
}
;
