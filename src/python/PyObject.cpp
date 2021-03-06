#include "PyObject.h"
#include "Caret.h"
#include "FunctionCall.h"
#include "Indexed.h"
#include "Parenthesis.h"
#include "LessEqual.h"
#include "Less.h"
#include "Greater.h"
#include "GreaterEqual.h"
#include "Equal.h"
#include "Unequal.h"
#include "Contains.h"
#include "NotContains.h"
#include "LogicNot.h"
#include "LogicAnd.h"
#include "LogicOr.h"
#include "Set.h"
#include "Tuple.h"
#include "ArrayList.h"
#include "IfElse.h"
#include "Generator.h"
#include "GeneratorIf.h"
#include "GeneratorAsync.h"
#include "Dot.h"

map<string, PyObject::MFPTR> PyObject::fpntr = []() -> map<string,
		PyObject::MFPTR> {
	map<string, PyObject::MFPTR> dict;
	dict["for"] = &PyObject::append_keyword_for;
	dict["in"] = &PyObject::append_keyword_in;
	dict["and"] = &PyObject::append_keyword_and;
	dict["or"] = &PyObject::append_keyword_or;
	dict["if"] = &PyObject::append_keyword_if;
	dict["else"] = &PyObject::append_keyword_else;
	dict["is"] = &PyObject::append_keyword_is;
	dict["not"] = &PyObject::append_keyword_not;
	dict["async"] = &PyObject::append_keyword_async;
	return dict;
}();


PyObject* PyObject::append_left_parenthesis() {
	auto self = this;
	auto parent = self->parent;

	auto caret = new Caret();
	if (parent->instanceof<Dot>()) {
		self = parent;
		parent = self->parent;
	}

	if (parent->instanceof<Dot>()) {
		throw std::runtime_error("parent->instanceof<Dot>()?");
	}

	auto func = new FunctionCall(self, {
			caret
	}, parent);

	parent->replace(self, func);

	return caret;
}

PyObject* PyObject::append_colon(self) {
	child = (function (self) {
				do {
					parent = self->parent;
					if (parent->instanceof<Indexed>() || parent->instanceof<Set>()) {
						return null;
					}

					if (parent->instanceof<Lambda>() || parent->instanceof<Colon>()) {
						break;
					}
					self = parent;
				}while (parent !== null);

				return self;
			})(self);

	if (child !== null) {
		return child->parent->append_colon(child);
	}

	auto caret = new Caret();

	auto colon = new Colon({
			self,
			caret
	}, this);

	this->replace(self, colon);

	return caret;
}

PyObject* PyObject::append_left_bracket() {
	auto parent = this->parent;

	auto caret = new Caret();
	auto func = new Indexed(this, {
			caret
	}, parent);

	parent->replace(this, func);

	return caret;
}

PyObject* PyObject::append_comma(PyObject *obj) {
	return this->parent->append_comma(this);
}

PyObject* PyObject::append_semicolon(PyObject *obj) {
	return this->parent->append_semicolon(this);
}

PyObject* PyObject::append_right_bracket() {
	if (this->parent == nullptr) {
		throw std::runtime_error("this's parent is null!");
	}
	return this->parent->append_right_bracket();
}

PyObject* PyObject::append_right_brace() {
	if (this->parent == nullptr) {
		throw std::runtime_error("this's parent is null!");
	}
	return this->parent->append_right_brace();
}

PyObject* PyObject::append_right_parenthesis() {
	if (this->parent == nullptr) {
		throw std::runtime_error("this's parent is null!");
	}
	return this->parent->append_right_parenthesis();
}

PyObject* PyObject::printf() {
	caret = this;
	while (caret != null) {
		print (caret);
		caret = caret->parent;
	}
	print('\n');
}

PyObject* PyObject::append_keyword_for() {
	auto self = this;

	do {
		auto parent = self->parent;
		if (parent->instanceof<Parenthesis>() || parent->instanceof<FunctionCall>() || parent->instanceof<ArrayList>() || parent->instanceof<Set>()) {

			auto domain = new Caret();
			auto var = new Caret();
			auto generator = new Generator(self, var, domain, parent);
			parent->replace(self, generator);
			return var;
		} else {
			if (parent == nullptr) {
				break;
			}
			self = parent;
		}
	} while (true);
	return nullptr;
}

PyObject* PyObject::append_keyword_in() {
	parent = this->parent;
	while (parent->instanceof<Comma>() || parent->instanceof<Star>()) {
		parent = parent->parent;
	}

	if (parent->instanceof<Generator>()) {
		if (parent->domain->instanceof<Caret>())
			return parent->domain;
	}

	auto self = this;

	for (;;) {
		parent = self->parent;
		if (parent->instanceof<Dot>()) {
			self = parent;
			continue;
		}

		break;
	}

	auto caret = new Caret();
	auto contains = new Contains(self, caret, parent);
	parent->replace(self, contains);
	return caret;
}

PyObject* PyObject::append_keyword_and() {
	auto self = this;

	for (;;) {
		if (self->instanceof<FunctionCall>()) {
			break;
		}

		parent = self->parent;

		if (parent->instanceof<LessEqual>() || //
		parent->instanceof<Less>() ||//
		parent->instanceof<Greater>() ||//
		parent->instanceof<GreaterEqual>() ||//
		parent->instanceof<Equal>() ||//
		parent->instanceof<Unequal>() ||//
		parent->instanceof<Contains>() ||//
		parent->instanceof<NotContains>() ||//
		parent->instanceof<LogicNot>() ||//
		parent->instanceof<LogicAnd>()) {
			self = parent;
			break;
		}

		if (parent->instanceof<LogicOr>() || //
		parent->instanceof<Sentence>() ||//
		parent->instanceof<Parenthesis>() ||//
		parent->instanceof<IfElse>() ||//
		parent->instanceof<Set>() ||//
		parent->instanceof<Tuple>() ||//
		parent->instanceof<Indexed>() ||//
		parent->instanceof<FunctionCall>()) {
			break;
		}

		if (parent->instanceof<GeneratorIf>() && parent->cond == self) {
			break;
		}

		self = parent;
	}

	caret = new Caret();
	parent = self->parent;
	and = new LogicAnd(self, caret, parent);
	parent->replace(self, and);
	return caret;
}

PyObject* PyObject::append_keyword_or() {
	auto self = this;

	for (;;) {
		if (self->instanceof<FunctionCall>()) {
			break;
		}

		parent = self->parent;

		if (parent->instanceof<LessEqual>() || //
		parent->instanceof<Less>() ||//
		parent->instanceof<Greater>() ||//
		parent->instanceof<GreaterEqual>() ||//
		parent->instanceof<Equal>() ||//
		parent->instanceof<Unequal>() ||//
		parent->instanceof<Contains>() ||//
		parent->instanceof<NotContains>() ||//
		parent->instanceof<LogicNot>() ||//
		parent->instanceof<LogicAnd>() ||//
		parent->instanceof<LogicOr>()) {
			self = parent;
			break;
		}

		if (parent->instanceof<Sentence>() || //
		parent->instanceof<Parenthesis>() ||//
		parent->instanceof<IfElse>() ||//
		parent->instanceof<Set>() ||//
		parent->instanceof<Tuple>() ||//
		parent->instanceof<Indexed>() ||//
		parent->instanceof<FunctionCall>()) {
			break;
		}

		if (parent->instanceof<GeneratorIf>() && parent->cond == self) {
			break;
		}

		self = parent;
	}

	caret = new Caret();
	parent = self->parent;
	and = new LogicOr(self, caret, parent);
	parent->replace(self, and);
	return caret;
}

PyObject* PyObject::append_keyword_if() {
	auto self = this;

	for (;;) {
		auto parent = self->parent;
		if (parent->instanceof<Generator>()) {
			self = parent;
			parent = self->parent;
			auto caret = new Caret();

			class = get_class(self) . "If";
			new = new class(self->expr, self->var, self->domain, caret,
					parent);
			break;
		}
		// in the form {expr if cond else other}
		if (parent->instanceof<Set>() || //
		parent->instanceof<Parenthesis>() ||//
		parent->instanceof<ArrayList>() ||//
		parent->instanceof<Tuple>() ||//
		parent->instanceof<FunctionCall>() ||//
		parent->instanceof<Indexed>() ||//
		parent->instanceof<Sentence>()) {
			caret = new Caret();
			other = new Caret();
			new = new IfElse(self, caret, other, parent);
			break;
		}

		if (parent == nullptr) {
			throw std::runtime_error("illegal this in if statement ");
		}

		self = parent;
	}

	parent->replace(self, new);
	return caret;
}

PyObject* PyObject::append_keyword_else() {
	auto self = this;

	for (;;) {
		parent = self->parent;
		if (parent->instanceof<IfElse>()) {
			if (self == parent->cond) {
				return parent->other;
			}
			throw std::runtime_error("illegal this in else statement ");
		}

		if (parent == nullptr) {
			throw std::runtime_error("illegal this in else statement ");
		}

		self = parent;
	}

	parent->replace(self, $new);
	return caret;

}

PyObject* PyObject::append_keyword_is() {
	auto self = this;

	for (;;) {
		parent = self->parent;
		if (parent->instanceof<Dot>()) {
			self = parent;
			continue;
		}

		break;
	}
	caret = new Caret();
	is = new Is(self, caret, parent);
	parent->replace(self, is);
	return caret;
}

PyObject* PyObject::append_keyword_not() {
	auto self = this;

	for (;;) {
		parent = self->parent;
		if (parent->instanceof<Dot>()) {
			self = parent;
			continue;
		}

		break;
	}
	caret = new Caret();
	contains = new NotContains(self, caret, parent);
	parent->replace(self, contains);
	return caret;

}

PyObject* PyObject::append_keyword_async() {
	auto self = this;

	do {
		parent = self->parent;
		if (parent->instanceof<Parenthesis>() || parent->instanceof<FunctionCall>() || parent->instanceof<ArrayList>() || parent->instanceof<Set>()) {

			auto domain = new Caret();
			auto var = new Caret();
			auto generator = new GeneratorAsync(self, var, domain, parent);
			parent->replace(self, generator);
			return var;
		} else {
			if (parent == nullptr) {
				break;
			}
			self = parent;
		}
	} while (true);

	return nullptr;

}

PyObject* PyObject::append_identifier(const string &name) {
	if (fptr.count(name)) {
		return (*fptr[name]);
	} else {

		if (Literal::is_literal_prefix(name)) {
			auto literal = new Literal(name);
			auto parent = this->parent;
			if (parent->instanceof<Literals>()) {
				parent->args.push_back(literal);
				literal->parent = parent;
			} else {

				auto $new = new Literals({
						this,
						literal
				}, parent);

				parent->replace(this, $new);
			}
			return literal;
		}

		throw std::runtime_error(string("unrecognized keyword name with ") + this->parent->type() + " in " + __LINE__);
	}
}

void PyObject::replace(PyObject *old, PyObject *$new){
}

PyObject::~PyObject(){
}


PyObject* PyObject::newCaret(){
	return new Caret();
}
