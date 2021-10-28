// as in the form: expr if cond else other
#include "IfElse.h"

IfElse(PyObject *expr, PyObject *cond, PyObject *other, PyObject *parent)
{
	$this->expr = $expr;
	$this->cond = $cond;
	$this->other = $other;

	$cond->parent = $this;
	$expr->parent = $this;
	$other->parent = $this;

	$this->parent = $parent;
}

void IfElse::replace(PyObject *old, PyObject *$new) {
	if ($old === $this->expr) {
		$this->expr = $new;
	} else if ($old === $this->cond) {
		$this->cond = $new;
	} else if ($old === $this->other) {
		$this->other = $new;
	} else
		throw std::runtime_error(
				"void replace(TreeNode old, TreeNode replacement) throws Exception");
}

string IfElse::toString() {
	return "$this->expr if $this->cond else $this->other";
}

string IfElse::type() {
	return "$this->expr if $this->cond else $this->other";
}

