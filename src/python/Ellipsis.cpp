#include "Ellipsis.h"

Ellipsis::Ellipsis(PyObject *parent) {
	this->parent = parent;
}

Ellipsis::input_precedence() {
	return 0;
}

Ellipsis::stack_precedence() {
	return 0;
}

string Ellipsis::toString() {
	return "...";
}
