// as in the form x, y, z or x, y, z,
#pragma once

struct Comma : MultiVariableOperator
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
        return implode(", ", array_map(fn ($node) => $node->toString(), $this->args));
    }
}
;
