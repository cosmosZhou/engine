#pragma once

struct Dot : BinaryOperator
{

    static function input_precedence()
    {
        return 10;
    }

    static function stack_precedence()
    {
        return 20;
    }

    function toString()
    {
        return "$this->lhs.$this->rhs";
    }
}
;
