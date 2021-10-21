// as in the form: i for i in (1, 2, 3)
#pragma once

struct Generator : PyObject
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
    $var;

    protected $domain;

    protected $expr;

    function __construct($expr, $var, $domain, $parent)
    {
        $this->expr = $expr;
        $this->var = $var;
        $this->domain = $domain;

        $var->parent = $this;
        $expr->parent = $this;
        $domain->parent = $this;

        $this->parent = $parent;
    }

    function replace($old, $new)
    {
        if ($old === $this->expr) {
            $this->expr = $new;
        } else if ($old === $this->var) {
            $this->var = $new;
        } else if ($old === $this->domain) {
            $this->domain = $new;
        } else
            throw new RuntimeException("void replace(TreeNode old, TreeNode replacement) throws Exception");
    }

    function toString()
    {
        return "$this->expr for $this->var in $this->domain";
    }

    function append_comma($child)
    {
        if ($child === $this->var) {

            $caret = new Caret();
            $comma = new Comma([
                $this->var,
                $caret
            ], $this);
            $this->replace($this->var, $comma);
            return $caret;
        } else {
            throw new RuntimeException("illegal $child in $this for append_comma");
        }
    }
}
;
