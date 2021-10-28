#include "Generator.h"
#include "Comma.h"
#include "Caret.h"

PyObject* Generator::append_comma(PyObject *child) {
	if (child == this->var) {

		auto caret = new Caret();
		auto comma = new Comma( { this->var, caret }, this);

		this->replace(this->var, comma);
		return caret;
	} else {
		throw std::runtime_error("illegal $child in $this for append_comma");
	}
}
