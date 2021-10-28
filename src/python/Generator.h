// as in the form: i for i in (1, 2, 3)
#pragma once
#include "PyObject.h"
struct Generator : PyObject
{
	__declare_common_interface(0, 0);

    // must be an identifier, or a list of identifiers
	PyObject *var;

	PyObject *domain;

	PyObject *expr;

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

    void replace(PyObject *old, PyObject *$new)
    {
        if ($old === $this->expr) {
            $this->expr = $new;
        } else if ($old === $this->var) {
            $this->var = $new;
        } else if ($old === $this->domain) {
            $this->domain = $new;
        } else
            throw std::runtime_error("void replace(TreeNode old, TreeNode replacement) throws Exception");
    }

    string toString()
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
            throw std::runtime_error("illegal $child in $this for append_comma");
        }
    }
}
;
