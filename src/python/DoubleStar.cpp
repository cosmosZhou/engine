#pragma once

struct DoubleStar : UnaryOperator
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
        return "**$this->arg";
    }
}

;