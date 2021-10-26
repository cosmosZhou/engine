// as in the form (x, y, z) or (x, y, z, ) or (x, )
#pragma once

struct Tuple : MultiVariableOperator
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
        return "(" . implode(", ", array_map(fn ($node) => $node->toString(), $this->args)) . ")";
    }

    function append_right_parenthesis()
    {
        return $this;
    }
}
;
