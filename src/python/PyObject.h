#pragma once
#include <string>
using std::string;
#include <map>
using std::map;
#include <vector>
using std::vector;
#include <exception>

struct PyObject {
	PyObject* append_left_parenthesis();

	PyObject* append_colon(PyObject *self);

	PyObject* append_left_bracket();

	PyObject* append_comma(PyObject *obj);

	PyObject* append_semicolon(PyObject *obj);

	PyObject* append_right_bracket();

	PyObject* append_right_brace();

	PyObject* append_right_parenthesis();

	PyObject* append_binary_operator(const string &InputType, PyObject *child);

	void printf();

	PyObject* append_identifier(const string &name);

	string toString();

	PyObject *parent = nullptr;

	typedef PyObject* (PyObject::*MFPTR)();
	static map<string, MFPTR> fpntr;

	PyObject* append_keyword_for();
	PyObject* append_keyword_in();
	PyObject* append_keyword_and();
	PyObject* append_keyword_or();
	PyObject* append_keyword_if();
	PyObject* append_keyword_else();
	PyObject* append_keyword_is();
	PyObject* append_keyword_not();
	PyObject* append_keyword_async();

	virtual void replace(PyObject *old, PyObject *$new);

	virtual string type();
	bool instanceof(const string &type);

	virtual ~PyObject();

	template<typename InputType>
	PyObject* append_binary_operator(PyObject* child) {
		if (InputType::_input_precedence > this->stack_precedence()) {
			auto caret = new Caret();
			auto $new = new InputType(child, caret, this);

			this->replace(child, $new);
			return caret;
		}

		if (this->parent == nullptr) {
			throw new std::runtime_error("this 's parent == nullptr in append_binary_operator(InputType, child)");
		}

		return this->parent->append_binary_operator<InputType>(this);
	}
};

