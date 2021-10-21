#pragma once

struct Literals : MultiVariableOperator
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
        return implode(" ", array_map(fn ($node) => $node->toString(), $this->args));
    }

    function append_comma($child)
    {
        return $this->parent->append_comma($this);
    }
}


;
