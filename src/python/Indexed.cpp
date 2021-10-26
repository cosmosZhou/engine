#pragma once

struct Indexed : MultiVariableOperator
{

    static function input_precedence()
    {
        return 0;
    }

    static function stack_precedence()
    {
        return 0;
    }

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

    function toString()
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
