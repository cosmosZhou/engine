#pragma once

struct SubAssignment : BinaryOperator
{

    static function input_precedence()
    {
        return 10;
    }

    static function stack_precedence()
    {
        return 0;
    }

    function toString()
    {
        return "$this->lhs -= $this->rhs";
    }
}
;
