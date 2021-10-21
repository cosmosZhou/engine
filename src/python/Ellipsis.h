#pragma once

struct Ellipsis : PyObject
{

    function __construct($parent)
    {
        $this->parent = $parent;
    }

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
        return '...';
    }
};
