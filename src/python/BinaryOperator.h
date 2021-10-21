#pragma once

struct BinaryOperator : PyObject
{

function __construct($lhs, $rhs, $parent)
	{
		$this->lhs = $lhs;
		$this->rhs = $rhs;
		$lhs->parent = $rhs->parent = $this;
		$this->parent = $parent;
	}

$lhs;

$rhs;

	function replace($old, $new)
	{
		if ($this->lhs === $old) {
			$this->lhs = $new;
		} else if ($this->rhs === $old) {
			$this->rhs = $new;
		} else
		throw new RuntimeException("void replace(TreeNode old, TreeNode replacement) throws Exception");
	}
}
;
