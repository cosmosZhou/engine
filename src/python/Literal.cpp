#include "Literal.h"
#include "Literals.h"

PyObject* Literal::append_literal(string &infix, int &i, char mark) {
	int end = search_for_mark(infix, i, mark);

	if (end == i) {
		throw std::runtime_error("literal not found!");
	}

	auto $string = slice(infix, i, end);

	auto parent = this->parent;
	PyObject *caret = nullptr;
	if (parent->instanceof<Literals>()) {

		if (Literal::is_literal_prefix(this->literal)) {

			this->literal += $string;
			caret = this;
		} else {
			caret = new Literal($string, parent);
			parent->args.push_back(caret);
		}
	} else {
		caret = new Literal($string);
		auto $new = new Literals( { this, caret }, parent);

		parent->replace(this, $new);
	}

	i = end - 1;
	return caret;
}
