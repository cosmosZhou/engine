#pragma once

struct LogicNot : UnaryOperator
{

    static function input_precedence()
    {
        return 0;
    }

    static function stack_precedence()
    {
        return 0;
    }

    string toString()
    {
        return "not $this->arg";
    }
}
;
