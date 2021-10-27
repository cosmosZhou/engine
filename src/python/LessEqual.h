#pragma once
#include "BinaryOperator.h"
struct LessEqual : BinaryOperator
{
	__declare_common_interface(10, 0);
    string toString()
    {
        return "$this->lhs <= $this->rhs";
    }
}
;
