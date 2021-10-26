#pragma once

struct Identifier : PyObject
{

    static function input_precedence()
    {
        return 0;
    }

    static function stack_precedence()
    {
        return 0;
    }

    protected $name;

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

    function toString()
    {
        return $this->name;
    }

    function append_literal(&$infix, &$i, $mark)
    {
        if (! Literal::is_literal_prefix($this->name)) {
            throw new std::exception("illegal prefix $this->name before literal");
        }

        $end = search_for_mark($infix, $i, $mark);

        if ($end == $i) {
            throw new std::exception("literal not found!");
        }

        $prefix_length = strlen($this->name);
        $i -= $prefix_length;

        if (! \std\equals(substr($infix, $i, $prefix_length), $this->name)) {

            throw new std::exception("illegal prefix $this->name before literal: $infix");
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
