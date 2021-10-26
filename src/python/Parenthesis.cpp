#pragma once

struct Parenthesis : UnaryOperator
{

    static function input_precedence()
    {
        return 0;
    }

    static function stack_precedence()
    {
        return 0;
    }

    function append_right_parenthesis()
    {
        return $this;
    }

    function toString()
    {
        return "($this->arg)";
    }

    function append_comma($child)
    {
        $parent = $this->parent;
        $caret = new Caret();
        $tuple = new Tuple([
            $this->arg,
            $caret
        ], $parent);

        $parent->replace($this, $tuple);
        return $caret;
    }
}
;
