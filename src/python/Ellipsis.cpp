#include "Ellipsis.h"

Ellipsis::Ellipsis(PyObject *parent) {
	this->parent = parent;
}

string Ellipsis::toString() {
	return "...";
}
