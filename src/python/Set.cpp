#pragma once

struct Set : MultiVariableOperator
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
        return "{" . implode(", ", array_map(fn ($node) => $node->toString(), $this->args)) . "}";
    }

    function append_right_brace()
    {
        return $this;
    }
}
;
