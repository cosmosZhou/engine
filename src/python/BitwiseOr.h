#pragma once
#include "BinaryOperator.h"
struct BitwiseOr : BinaryOperator
{
	__declare_common_interface(12, 0);

    string toString()
    {
        return "$this->lhs | $this->rhs";
    }
}
;
