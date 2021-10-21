#pragma once

struct MultiVariableOperator : PyObject
{

    function __construct(array $args, $parent)
    {
        $this->args = $args;
        foreach ($args as $arg) {
            $arg->parent = $this;
        }

        $this->parent = $parent;
    }

    $args;

    function replace($old, $new)
    {
        $i = array_search($old, $this->args, true);
        if ($i === false)
            throw new RuntimeException("void replace(TreeNode old, TreeNode replacement) throws Exception");
        $this->args[$i] = $new;
    }

    function append_comma($child)
    {
        $caret = new Caret($this);
        $this->args[] = $caret;
        return $caret;
    }
}
;
