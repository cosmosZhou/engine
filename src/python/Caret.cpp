#include "Caret.h"

Caret::Caret(PyObject *parent) {
	this->parent = parent;
}

#include "Ellipsis.h"
PyObject* Caret::append_ellipsis() {
	parent = this->parent;
	auto $new = new Ellipsis(parent);
	parent->replace(this, $new);
	return $new;
}

#include "utility.h"

PyObject *Caret::append_literal(const string &infix, int &i, char mark)
{
	auto end = search_for_mark(infix, i, mark);

	if (end == i) {
		throw std::runtime_error("digits not found!");
	}

	auto string = slice(infix, i, end);

	parent = this->parent;
	caret = new Literal(string, parent);
	parent->replace(this, caret);

	i = end - 1;
	return caret;
}

PyObject *Caret::append_digit(&infix, &i)
{
	end = search_for_digits(infix, i);

	if (end == i) {
		throw std::runtime_error("digits not found!");
	}

	digits = slice(infix, i, end);

	parent = this->parent;
	caret = new Number(digits, parent);
	parent->replace(this, caret);

	i = end - 1;
	return caret;
}

PyObject* Caret::append_left_brace() {
	caret = new Caret();

	parent = this->parent;
	set = new Set({caret}, parent);
	parent->replace(this, set);

	return caret;
}

PyObject* Caret::append_left_parenthesis() {
	caret = new Caret();

	parent = this->parent;
	parenthesis = new Parenthesis(caret, parent);
	parent->replace(this, parenthesis);

	return caret;
}

PyObject* Caret::append_identifier(name) {
	parent = this->parent;

	switch (name) {
	case "lambda":
		caret = new Caret();
		expr = new Caret();

		lambda = new Lambda(caret, expr, parent);
		parent->replace(this, lambda);
		break;
	case "not":
		not = new LogicNot(this, parent);
		parent->replace(this, not);
		caret = this;
		break;
	case "if":
		throw std::runtime_error("illegal if statement here");
		// not = new LogicNot(this, parent);
		// parent->replace(this, not);
		// caret = this;
		break;
	case "in":
		if (parent instanceof NotContains) {
			if (parent->in_is_received) {
				throw std::runtime_error(
						"illegal in statement here in parent");
			}
			parent->in_is_received = true;
		} else {
			throw std::runtime_error("illegal in statement here in parent");
		}

		caret = this;
		break;

	case "await":
		caret = this;
		new = new Await(caret, parent);
		parent->replace(this, new);
		break;

	case "yield":
		caret = this;
		new = new GeneratorYield(caret, parent);
		parent->replace(this, new);
		break;

	case "from":
		parent = this->parent;
		if (parent instanceof GeneratorYield) {
			forefather = parent->parent;
		new = new GeneratorYieldFrom(this, forefather);
		forefather->replace(parent, new);
	} else {
		throw std::runtime_error("illegal from statement of this in parent");
	}

	caret = this;
	break;

case "for":
	parent = this->parent;
	if (parent instanceof GeneratorAsync) {
		if (this !== parent->var) {
			throw std::runtime_error(
					"illegal from statement of this in parent");
		}
	} else {
		throw std::runtime_error("illegal from statement of this in parent");
	}

	caret = this;
	break;

default:
	caret = new Identifier(name, parent);
	parent->replace(this, caret);
	}

	return caret;
}

string Caret::toString() {
	return "";
}

PyObject* Caret::append_left_bracket() {
	parent = this->parent;

	func = new ArrayList([
			this
			], parent);

	parent->replace(this, func);

	return this;
}
