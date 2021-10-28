#pragma once

struct Number : PyObject
{
	__declare_common_interface(0, 0);

    PyObject *$digits;

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
