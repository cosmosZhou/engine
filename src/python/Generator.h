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

	Generator(PyObject *expr, PyObject *var, PyObject *domain, PyObject *parent): PyObject(parent), var(var), domain(domain), expr(expr)
    {
        var->parent = this;
        expr->parent = this;
        domain->parent = this;
    }

    void replace(PyObject *old, PyObject *$new)
    {
        if (old == this->expr) {
            this->expr = $new;
        } else if (old == this->var) {
            this->var = $new;
        } else if (old == this->domain) {
            this->domain = $new;
        } else
            throw std::runtime_error("void replace(TreeNode old, TreeNode replacement) throws Exception");
    }


    string toString()
    {
    	ostringstream cout;
    	cout << this->expr->toString() << " for " << this->var->toString() << " in " << this->domain->toString();
    	return cout.str();
    }

    PyObject *append_comma(PyObject *child);
};
