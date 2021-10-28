#include "Sentence.h"
#include "Caret.h"
#include "Set.h"

PyObject* Sentence::append_left_brace() {
	auto caret = new Caret();
	this->args.push_back(new Set( { caret, this }));
	return caret;
}

PyObject* Sentence::append_left_parenthesis() {
	auto caret = new Caret();
	this->args.push_back(new Set( { caret, this }));
	return caret;
}


PyObject* Sentence::append_comma(PyObject *child) {
	auto obj = this->args.back();
	auto caret = new Caret();
	auto comma = new Comma( { obj, caret }, this);
	this->replace(obj, comma);
	return caret;
}

PyObject* Sentence::append_semicolon(PyObject *child) {
	auto caret = new Caret(this);
	this->args.push_back(caret);
	return caret;
}
