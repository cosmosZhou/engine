#pragma once
#include "MultiVariableOperator.h"

int FunctionCall::input_precedence() {
	return 0;
}

int FunctionCall::stack_precedence() {
	return 0;
}

FunctionCall::FunctionCall(PyObject *name, vector<PyObject*> $args, PyObject*parent)
{
	parent::__construct($args, $parent);
	$this->name = $name;
	$name->parent = $this;
}

PyObject *FunctionCall::append_right_parenthesis() {
	return this;
}

string FunctionCall::toString() {
	return "$this->name(" + implode(", ", array_map(fn ($obj) => $obj->toString(), $this->args)) . ')';
}

void FunctionCall::replace(PyObject *old, PyObject *$new) {
	if ($old === $this->name) {
		$this->name = $new;
	} else {
		parent::replace($old, $new);
	}
}
