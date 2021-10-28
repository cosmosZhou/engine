#include "Colon.h"
#include "Caret.h"
PyObject* Colon::append_colon() {
	auto caret = new Caret(this);
	this->args.push_back(caret);
	return caret;
}
