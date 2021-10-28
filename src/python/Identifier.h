#pragma once

struct Identifier : PyObject
{
	__declare_common_interface(0, 0);

    PyObject *$name;

    function __construct(string $name, $parent)
    {
        $this->name = $name;
        $this->parent = $parent;
    }

    function append_left_brace()
    {
        $caret = new Caret();
        $parent = $this->parent;
        $new = new TreeNodePrefix($this->name, new Set($caret), $parent);
        $parent->replace($this, $new);
        return $caret;
    }

    string toString()
    {
        return $this->name;
    }

    function append_literal(&$infix, &$i, $mark)
    {
        if (! Literal::is_literal_prefix($this->name)) {
            throw std::runtime_error("illegal prefix $this->name before literal");
        }

        $end = search_for_mark($infix, $i, $mark);

        if ($end == $i) {
            throw std::runtime_error("literal not found!");
        }

        $prefix_length = strlen($this->name);
        $i -= $prefix_length;

        if (! \std\equals(substr($infix, $i, $prefix_length), $this->name)) {

            throw std::runtime_error("illegal prefix $this->name before literal: $infix");
        }

        $string = \std\slice($infix, $i, $end);

        $parent = $this->parent;
        $caret = new Literal($string, $parent);
        $parent->replace($this, $caret);

        $i = $end - 1;
        return $caret;
    }
}

;
