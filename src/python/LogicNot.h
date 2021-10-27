#pragma once
#include "BinaryOperator.h"
struct LogicNot : UnaryOperator
{
	__declare_common_interface(0, 0);

    string toString()
    {
        return "not $this->arg";
    }
}
;
