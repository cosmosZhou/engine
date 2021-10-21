#include <string>
using std::string;

int Caret::input_precedence()
{
	return 0;
}

int Caret::stack_precedence()
{
	return 0;
}

Caret::Caret(PyObject *parent)
{
	this->parent = parent;
}

PyObject *Caret::append_ellipsis()
{
	parent = this->parent;
	new = new Ellipsis(parent);
	parent->replace(this, new);
	return new;
}

PyObject *Caret:: append_literal(&infix, &i, mark)
{
	end = search_for_mark(infix, i, mark);

	if (end == i) {
		throw new RuntimeException("digits not found!");
	}

	string = \std\slice(infix, i, end);

	parent = this->parent;
	caret = new Literal(string, parent);
	parent->replace(this, caret);

	i = end - 1;
	return caret;
}

PyObject *Caret:: append_digit(&infix, &i)
{
	end = search_for_digits(infix, i);

	if (end == i) {
		throw new RuntimeException("digits not found!");
	}

	digits = \std\slice(infix, i, end);

	parent = this->parent;
	caret = new Number(digits, parent);
	parent->replace(this, caret);

	i = end - 1;
	return caret;
}

PyObject *Caret:: append_left_brace()
{
	caret = new Caret();

	parent = this->parent;
	set = new Set([
		caret
	], parent);
	parent->replace(this, set);

	return caret;
}

PyObject *Caret:: append_unary_operator(class)
{
	parent = this->parent;

	new = new class(this, parent);

	parent->replace(this, new);

	return this;
}

PyObject *Caret:: append_left_parenthesis()
{
	caret = new Caret();

	parent = this->parent;
	parenthesis = new Parenthesis(caret, parent);
	parent->replace(this, parenthesis);

	return caret;
}

PyObject *Caret:: append_identifier(name)
{
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
			throw new RuntimeException('illegal if statement here');
			// not = new LogicNot(this, parent);
			// parent->replace(this, not);
			// caret = this;
			break;
		case "in":
			if (parent instanceof NotContains) {
				if (parent->in_is_received) {
					throw new RuntimeException('illegal in statement here in parent');
				}
				parent->in_is_received = true;
			} else {
				throw new RuntimeException('illegal in statement here in parent');
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
				throw new RuntimeException("illegal from statement of this in parent");
			}

			caret = this;
			break;

		case "for":
			parent = this->parent;
			if (parent instanceof GeneratorAsync) {
				if (this !== parent->var) {
					throw new RuntimeException("illegal from statement of this in parent");
				}
			} else {
				throw new RuntimeException("illegal from statement of this in parent");
			}

			caret = this;
			break;

		default:
			caret = new Identifier(name, parent);
			parent->replace(this, caret);
	}

	return caret;
}

string Caret::toString()
{
	return "";
}

PyObject *Caret:: append_left_bracket()
{
	parent = this->parent;

	func = new ArrayList([
		this
	], parent);

	parent->replace(this, func);

	return this;
}
