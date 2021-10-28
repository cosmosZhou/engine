#pragma once
#include <string>
using std::string;
#include <map>
using std::map;
#include <set>
using std::set;

#include <vector>
using std::vector;
#include <exception>
#include <typeinfo>
using std::type_info;
#include <iostream>
using std::ostream;

#include "../std/utility.h"

struct PyObject {
	PyObject(PyObject *parent = nullptr) :
			parent(parent) {
	}

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

	virtual const type_info& type();

	template<typename $class>
	bool instanceof() {
		return dynamic_cast<$class*>(this);
	}

	virtual int stack_precedence() = 0;
	virtual int input_precedence() = 0;

	virtual ~PyObject();

	template<typename $class>
	PyObject* append_binary_operator(PyObject *child) {
		if ($class::_input_precedence > this->stack_precedence()) {
			auto caret = newCaret();
			auto $new = new $class(child, caret, this);

			this->replace(child, $new);
			return caret;
		}

		if (this->parent == nullptr) {
			throw std::runtime_error(
					"this 's parent == nullptr in append_binary_operator(InputType, child)");
		}

		return this->parent->append_binary_operator<$class>(this);
	}

	friend ostream& operator <<(ostream &cout, PyObject *self) {
		cout << self->toString();
		return cout;
	}

	friend ostream& operator <<(ostream &cout, PyObject &self) {
		cout << self.toString();
		return cout;
	}

	PyObject* newCaret();
	virtual bool is_Caret(){
		return false;
	}

	template<typename $class>
	PyObject* append_unary_operator() {
		if (this->is_Caret()) {
			auto parent = this->parent;

			auto $new = new $class(this, parent);

			parent->replace(this, $new);

			return this;
		}
		return nullptr;
	}

};

#define __declare_common_interface(input, stack)\
const static int _input_precedence = input;\
const static int _stack_precedence = stack;\
int input_precedence(){\
	return _input_precedence;\
}\
int stack_precedence(){\
	return _stack_precedence;\
}\
const type_info &type(){\
	return typeid(*this);\
}

