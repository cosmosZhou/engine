#pragma once

struct Number : PyObject
{

    static function input_precedence()
    {
        return 0;
    }

    static function stack_precedence()
    {
        return 0;
    }

    protected $digits;

    function __construct(string $digits, $parent)
    {
        $this->digits = $digits;
        $this->parent = $parent;
    }

    string toString()
    {
        return $this->digits;
    }
}
;
