#pragma once
#include "BinaryOperator.h"

struct BitwiseAnd : BinaryOperator
{

    int input_precedence();
    int stack_precedence();
    string toString();
    string type();
};
