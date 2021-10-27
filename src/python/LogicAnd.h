#pragma once
#include "BinaryOperator.h"
struct LogicAnd : BinaryOperator
{
	__declare_common_interface(0, 0);

    string toString()
    {
        return "$this->lhs and $this->rhs";
    }
}
;
