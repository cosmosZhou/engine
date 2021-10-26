#pragma once

struct NotContains : BinaryOperator
{

    static function input_precedence()
    {
        return 0;
    }

    static function stack_precedence()
    {
        return 0;
    }

    $in_is_received = false;

    function toString()
    {
        return "$this->lhs not in $this->rhs";
    }
}
;
