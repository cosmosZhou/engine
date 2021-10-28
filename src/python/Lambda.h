// as in the form: lambda x, y : x + y
#pragma once

struct Lambda : PyObject
{
	__declare_common_interface(0, 0);

    // must be an identifier, or a list of identifiers
    PyObject *$var;

    PyObject *$expr;

    function __construct($var, $expr, $parent)
    {
        $this->expr = $expr;
        $this->var = $var;

        $var->parent = $this;
        $expr->parent = $this;

        $this->parent = $parent;
    }

    void replace(PyObject *old, PyObject *$new)
    {
        if ($old === $this->expr) {
            $this->expr = $new;
        } else if ($old === $this->var) {
            $this->var = $new;
        } else
            throw std::runtime_error("void replace(TreeNode old, TreeNode replacement) throws Exception");
    }

    string toString()
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
            throw std::runtime_error('illegal $child for lambda expression $this');
        }
    }

    function append_colon($self)
    {
        if ($self === $this->var) {
            return $this->expr;
        } else {
            throw std::runtime_error("$this could not accept more slice args!");
        }
    }
}
;
