#pragma once
#include "UnaryOperator.h"
struct Star : UnaryOperator
{
	__declare_common_interface(0, 0);
    string toString()
    {
        return "*$this->arg";
    }
}
;
