#pragma once
#include "BinaryOperator.h"
struct NotContains : BinaryOperator
{
	__declare_common_interface(0, 0);

    $in_is_received = false;

    string toString()
    {
        return "$this->lhs not in $this->rhs";
    }
}
;
