#pragma once

struct UnaryOperator : PyObject
{

    static function input_precedence()
    {
        return 0;
    }

    static function stack_precedence()
    {
        return 0;
    }

    function __construct($arg, $parent)
    {
        $this->arg = $arg;
        $arg->parent = $this;
        $this->parent = $parent;
    }

    protected $arg;

    function replace($old, $new)
    {
        if ($this->arg === $old) {
            $this->arg = $new;
        } else
            throw new std::exception("void replace(TreeNode old, TreeNode replacement) throws Exception");
    }
}
;
