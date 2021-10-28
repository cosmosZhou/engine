// as in the form: i async for i in (1, 2, 3) if i
#pragma once
#include "GeneratorAsync.h"
struct GeneratorAsyncIf : GeneratorAsync
{
	__declare_common_interface(0, 0);

    PyObject *$cond;

    function __construct($expr, $var, $domain, $cond, $parent)
    {
        parent::__construct($expr, $var, $domain, $parent);
        $this->cond = $cond;

        $cond->parent = $this;
    }

    void replace(PyObject *old, PyObject *$new)
    {
        if ($old === $this->cond) {
            $this->cond = $new;
        } else {
            parent::replace($old, $new);
        }
    }

    string toString()
    {
        return parent::toString() . " if $this->cond";
    }
}
;
