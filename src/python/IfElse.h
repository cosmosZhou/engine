// as in the form: expr if cond else other
#pragma once

struct IfElse : PyObject
{

    static function input_precedence()
    {
        return 0;
    }

    static function stack_precedence()
    {
        return 0;
    }

    // must be an identifier, or a list of identifiers
    protected $expr;

    protected $cond;

    $other;

    function __construct($expr, $cond, $other, $parent)
    {
        $this->expr = $expr;
        $this->cond = $cond;
        $this->other = $other;

        $cond->parent = $this;
        $expr->parent = $this;
        $other->parent = $this;

        $this->parent = $parent;
    }

    function replace($old, $new)
    {
        if ($old === $this->expr) {
            $this->expr = $new;
        } else if ($old === $this->cond) {
            $this->cond = $new;
        } else if ($old === $this->other) {
            $this->other = $new;
        } else
            throw new std::exception("void replace(TreeNode old, TreeNode replacement) throws Exception");
    }

    function toString()
    {
        return "$this->expr if $this->cond else $this->other";
    }
}
;
