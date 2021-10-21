#pragma once
#include <string>
using std::string;

#include "PyObject.h"

struct Caret : PyObject
{

    static int input_precedence();

    static int stack_precedence();

    Caret(PyObject *parent = 0);

    PyObject *append_ellipsis();

    PyObject *append_literal(const string &infix, int &i, char mark);

    PyObject *append_digit(string &infix, int &i);

    PyObject *append_left_brace();

    PyObject *append_unary_operator(const string &$class);

    PyObject *append_left_parenthesis();

    PyObject *append_identifier(const string &name);

    string toString();

    PyObject *append_left_bracket();
};
