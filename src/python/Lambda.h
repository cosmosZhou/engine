// as in the form: lambda x, y : x + y
#pragma once

struct Lambda : PyObject
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
    protected $var;

    protected $expr;

    function __construct($var, $expr, $parent)
    {
        $this->expr = $expr;
        $this->var = $var;

        $var->parent = $this;
        $expr->parent = $this;

        $this->parent = $parent;
    }

    function replace($old, $new)
    {
        if ($old === $this->expr) {
            $this->expr = $new;
        } else if ($old === $this->var) {
            $this->var = $new;
        } else
            throw new RuntimeException("void replace(TreeNode old, TreeNode replacement) throws Exception");
    }

    function toString()
    {
        return "lambda $this->var : $this->expr";
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
        } else if ($child === $this->expr) {
            return parent::append_comma($child);
        } else {
            throw new RuntimeException('illegal $child for lambda expression $this');
        }
    }

    function append_colon($self)
    {
        if ($self === $this->var) {
            return $this->expr;
        } else {
            throw new RuntimeException("$this could not accept more slice args!");
        }
    }
}
;
