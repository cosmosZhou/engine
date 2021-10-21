#pragma once

struct BitwiseAnd : BinaryOperator
{

    static function input_precedence()
    {
        return 12;
    }

    static function stack_precedence()
    {
        return 0;
    }

    function toString()
    {
        return "$this->lhs & $this->rhs";
    }
}
;
