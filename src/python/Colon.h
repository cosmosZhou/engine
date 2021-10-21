// as in the form start:stop:step, or as in the form {k:v, k1:v2}
#pragma once

struct Colon : MultiVariableOperator
{

    static function input_precedence()
    {
        return 0;
    }

    static function stack_precedence()
    {
        return 0;
    }

    function append_colon($self)
    {
        $caret = new Caret($this);
        $this->args[] = $caret;
        return $caret;
    }

    function toString()
    {
        return implode(":", array_map(fn ($node) => $node->toString(), $this->args));
    }

    function append_comma($child)
    {
        return $this->parent->append_comma($this);
    }
}
;
