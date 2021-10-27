#pragma once

struct BitwiseOr : BinaryOperator
{

    static function input_precedence()
    {
        return 12;
    }

    static function stack_precedence()
    {
        return 0;
    }

    string toString()
    {
        return "$this->lhs | $this->rhs";
    }
}
;
