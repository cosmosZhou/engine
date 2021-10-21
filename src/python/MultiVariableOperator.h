#pragma once
#include "MultiVariableOperator.h"

MultiVariableOperator::MultiVariableOperator(vector<PyObject*> &args, PyObject *parent)
{
	this->args = args;
	for (auto arg : args) {
		arg->parent = this;
	}

	this->parent = parent;
}

void MultiVariableOperator::replace(PyObject *old, PyObject *$new)
{
	int i = indexOf(this->args, old);
	if (i < 0)
		throw new std::exception("void replace(PyObject *old, PyObject *replacement)");
	this->args[i] = $new;
}

PyObject *MultiVariableOperator::append_comma(PyObject *child)
{
	auto caret = new Caret(this);
	this->args.push_back(caret);
	return caret;
}

MultiVariableOperator::~MultiVariableOperator(){

}
