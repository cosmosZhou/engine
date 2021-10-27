#pragma once

struct Parenthesis : UnaryOperator
{
	__declare_common_interface(0, 0);

    function append_right_parenthesis()
    {
        return $this;
    }

    string toString()
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
