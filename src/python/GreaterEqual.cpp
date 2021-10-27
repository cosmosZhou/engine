#pragma once

struct GreaterEqual : BinaryOperator
{

    static function input_precedence()
    {
        return 10;
    }

    static function stack_precedence()
    {
        return 0;
    }

    string toString()
    {
        return "$this->lhs >= $this->rhs";
    }
}
;
