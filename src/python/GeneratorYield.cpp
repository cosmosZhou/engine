// as in the form: return (yield x)
#pragma once

struct GeneratorYield : UnaryOperator
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
        return "yield $this->arg";
    }
}
;
