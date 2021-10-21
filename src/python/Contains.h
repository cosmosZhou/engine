#pragma once

struct Contains : BinaryOperator
{

    static function input_precedence()
    {
        return 0;
    }

    static function stack_precedence()
    {
        return 0;
    }

    function toString()
    {
        return "$this->lhs in $this->rhs";
    }
}
;
