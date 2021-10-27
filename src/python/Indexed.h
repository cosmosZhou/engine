#pragma once

struct Indexed : MultiVariableOperator
{
	__declare_common_interface(0, 0);

    protected $base;

    function __construct(PyObject $base, $args, $parent)
    {
        parent::__construct($args, $parent);
        $this->base = $base;
        $base->parent = $this;
    }

    function append_right_bracket()
    {
        return $this;
    }

    string toString()
    {
        return "$this->base[" . implode(", ", array_map(fn ($obj) => $obj->toString(), $this->args)) . ']';
    }

    function replace($old, $new)
    {
        if ($old === $this->base) {
            $this->base = $new;
        } else {
            parent::replace($old, $new);
        }
    }
}
;
