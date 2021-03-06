#include "../std/utility.h"
#include "PyObject.h"
#include "IfElse.h"
#include "Caret.h"

#include "FunctionCall.h"
#include "ArrayList.h"
#include "Tuple.h"
#include "Parenthesis.h"
#include "Indexed.h"
#include "Set.h"
#include "Comma.h"

int search_for_identifier(const string &infix, int i) {
	static char _ = 95; // ord('_');
	static char a = 97; // ord('a');
	static char z = 122; // ord('z');

	static char A = 65; // ord('A');
	static char Z = 90; // ord('Z');

	static char _0 = 48; // ord('0');
	static char _9 = 57; // ord('9');

	auto $strlen = infix.size();
	for (; i < $strlen; ++i) {
		ch = ord(infix[i]);
		if (ch >= a && ch <= z || ch >= A && ch <= Z || ch >= _0 && ch <= _9
				|| ch == _) {
			continue;
		} else if (ch >= 128) {
			i += TextC::get_utf8_char_len(ch) - 1;
		} else
			return i;
	}
	return i;
}

function search_for_digits(&infix, i)
{
	static _0 = 48; // ord('0');
	static _9 = 57;// ord('9');

	auto $strlen = infix.size();
	if (infix[i] == '0') {
		if (i + 1 < $strlen) {
			switch (infix[i + 1]) {
				case 'x':
				case 'X':

				static A = 65; // ord('A');
				static F = 70;// ord('F');

				static a = 97;// ord('a');
				static f = 102;// ord('f');

				i += 2;
				for (; i < $strlen; ++ i) {
					ch = ord(infix[i]);
					if (ch >= _0 && ch <= _9 || ch >= a && ch <= f || ch >= A && ch <= F) {
						continue;
					} else
					break;
				}

				return i;
				case 'o':
				case 'O':
				i += 2;
				static _7 = 55; // ord('7');
				for (; i < $strlen; ++ i) {
					ch = ord(infix[i]);
					if (ch >= _0 && ch <= _7) {
						continue;
					} else
					break;
				}

				return i;
			}
		}
	}

	for (; i < $strlen; ++ i) {
		ch = ord(infix[i]);
		if (ch >= _0 && ch <= _9) {
			continue;
		}

		switch (infix[i]) {
			case 'j':
			case 'J':
			++ i;
			default:
			return i;
			case '.':
			break;
			case 'e':
			case 'E':

			++ i;
			switch (infix[i]) {
				case '+':
				case '-':
				++ i;
				break;
				default:
				break;
			}

			for (; i < $strlen; ++ i) {
				ch = ord(infix[i]);
				if (ch >= _0 && ch <= _9) {
					continue;
				}

				switch (infix[i]) {
					case 'j':
					case 'J':
					++ i;
					default:
					return i;
				}
			}

			break;
		}
	}
	return i;
}

function search_for_mark(&infix, i, mark)
{
	$strlen = infix.size();
	for (++ i; i < $strlen; ++ i) {
		if (infix[i] == mark) {
			if (infix[i - 1] == '\\') {
				if (i >= 2 && infix[i - 2] == '\\') {
					return i + 1;
				}
			} else
			return i + 1;
		}
	}
	return i;
}

void append_identifier(PyObject *&caret, string &infix, int &i) {
	int end = search_for_identifier(infix, i);

	if (end == i) {
		throw std::runtime_error("lexeme not found!");
	}

	// \std\println(\std\slice(infix, i, end));

	caret = caret->append_identifier(slice(infix, i, end));

	i = end - 1;
}

PyObject* compile(string &infix, PyObject *&state, PyObject *caret = null) {
	if (caret == null) {
		caret = new Caret();
		auto sentence = new Sentence( { caret });
	}

	$strlen = infix.size();
	for (i = 0; i < $strlen; ++i) {
		ch = infix[i];
		switch (ch) {
		case "\t": // = 9;
			break;
		case "\n": // 0x0a;
			break;
		case "\v": // = 0x0b;
			break;
		case "\f": // = 0x0c;
			break;
		case "\r": // 0x0d;
			break;
		case "\x1b":
			break;

		case ' ':
			break;

		case '!':
			// unicodedata.name('!')
			if (i + 1 < $strlen && infix[i + 1] == '=') {
				++i;
				// x != y
				caret = caret->parent->append_binary_operator("Unequal", caret);
			} else {
				throw std::runtime_error("illegal character ch after !");
			}

			break;
		case '"':
			// unicodedata.name('"')
			caret = caret->append_literal(infix, i, ch);
			break;
		case '#':
			state["commentStart"] = i;
			return caret;
		case '$':
			// unicodedata.name("")
			caret = caret->append_dollarSign();
			break;

		case '%':
			// unicodedata.name("%")
			if (i + 1 < $strlen && infix[i + 1] == '=') {
				++i;
				$class = "ModAssignment";
			} else {
				$class = "Mod";
			}
			caret = caret->parent->append_binary_operator($class, caret);
			break;

		case '&':
			// unicodedata.name("&")
			if (i + 1 < $strlen && infix[i + 1] == '=') {
				++i;
				// x &= y
				$class = "BitwiseAndAssignment";
			} else {
				// x & y
				$class = "BitwiseAnd";
			}

			caret = caret->parent->append_binary_operator($class, caret);
			break;

		case '\'':
			// unicodedata.name("'")
			caret = caret->append_literal(infix, i, ch);
			break;
		case '(':
			caret = caret->append_left_parenthesis();
			break;
		case ')':
			caret = caret->parent->append_right_parenthesis();
			break;

		case '*':
			if (caret->instanceof<Caret>()) {
				if (i + 1 < $strlen && infix[i + 1] == '*') {
					++i;
					// **kwargs
					$class = "DoubleStar";
				} else {
					// **args
					$class = "Star";
				}

				caret = caret->append_unary_operator($class);
			} else {
				if (i + 1 < $strlen) {

					switch (infix[i + 1]) {
					case '=':
						++i;
						// x *= y
						$class = "MulAssignment";
						break;
					case '*':
						++i;
						if (i + 1 < $strlen && infix[i + 1] == '=') {
							++i;
							// x **= y
							$class = "PowAssignment";
						} else {
							$class = "Pow";
						}

						break;
					default:
						// x * y
						$class = "Mul";
						break;
					}
				} else {
					// x * y
					$class = "Mul";
				}

				caret = caret->parent->append_binary_operator($class, caret);
			}

			break;
		case '+':
			if (caret->instanceof<Caret>()) {
				caret = caret->append_unary_operator("Plus");
			} else {
				if (i + 1 < $strlen && infix[i + 1] == '=') {

					++i;
					// x += y
					$class = "AddAssignment";
				} else {
					// x + y
					$class = "Add";
				}

				caret = caret->parent->append_binary_operator($class, caret);
			}

			break;
		case ',':
			caret = caret->parent->append_comma(caret);
			break;
		case '-':
			if (caret->instanceof<Caret>()) {
				caret = caret->append_unary_operator("Neg");
			} else {
				if (i + 1 < $strlen && infix[i + 1] == '=') {

					++i;
					// x -= y
					$class = "SubAssignment";
				} else {
					// x - y
					$class = "Sub";
				}

				caret = caret->parent->append_binary_operator($class, caret);
			}

			break;
		case '.':
			if (i + 2 < $strlen && substr(infix, i, 3) == "...") {
				i += 2;
				caret = caret->append_ellipsis();
			} else {
				caret = caret->parent->append_binary_operator("Dot", caret);
			}

			break;
		case '/':
			if (i + 1 < $strlen) {

				switch (infix[i + 1]) {
				case '=':
					++i;
					// x /= y
					$class = "DivAssignment";
					break;
				case '/':
					++i;
					if (i + 1 < $strlen && infix[i + 1] == '=') {
						++i;
						// x //= y
						$class = "FloorDivAssignment";
					} else {
						// x // y
						$class = "FloorDiv";
					}

					break;
				default:
					// x / y
					$class = "Div";
					break;
				}
			} else {
				// x / y
				$class = "Div";
			}

			caret = caret->parent->append_binary_operator($class, caret);

			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			caret = caret->append_digit(infix, i);
			break;

		case ':':
			caret = caret->parent->append_colon(caret);
			break;

		case ';':
			caret = caret->parent->append_semicolon(caret);
			break;

		case '<':
			if (i + 1 < $strlen) {
				switch (infix[i + 1]) {
				case '=':
					++i;
					// x <= y
					$class = "LessEqual";
					break;
				case '<':
					++i;
					if (i + 1 < $strlen) {
						switch (infix[i + 1]) {
						case '=':
							++i;
							// x <<= y
							$class = "LeftShiftAssignment";
							break;
						default:
							// x << y
							$class = "LeftShift";
							break;
						}
					} else {
						// x << y
						$class = "LeftShift";
					}
					break;
				default:
					// x < y
					$class = "Less";
					break;
				}
			}

			caret = caret->parent->append_binary_operator($class, caret);
			break;

		case '=':
			if (i + 1 < $strlen && infix[i + 1] == '=') {
				++i;
				// x == y
				$class = "Equal";
			} else
				$class = "EqualAssignment";

			caret = caret->parent->append_binary_operator($class, caret);
			break;

		case '>':

			if (i + 1 < $strlen) {
				switch (infix[i + 1]) {
				case '=':
					++i;
					// x >= y
					$class = "GreaterEqual";
					break;
				case '>':
					++i;
					if (i + 1 < $strlen && infix[i + 1] == '=') {
						++i;
						// x >>= y
						$class = "RightShiftAssignment";
					} else
						// x >> y
						$class = "RightShift";
					break;
				default:
					// x > y
					$class = "Greater";
					break;
				}
			} else
				// x > y
				$class = "Greater";

			caret = caret->parent->append_binary_operator($class, caret);
			break;

		case '?':
			// unicodedata.name('?')
			caret = caret->append_QuestionMark();
			break;
		case '@':
			// unicodedata.name('@')
			if (i + 1 < $strlen && infix[i + 1] == '=') {
				++i;
				$class = "MatMulAssignment";
			} else
				$class = "MatMul";

			caret = caret->parent->append_binary_operator($class, caret);
			break;
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
			append_identifier(caret, infix, i);

			break;
		case '[':
			caret = caret->append_left_bracket();
			break;
		case '\\':
			// unicodedata.name('\\')
			if (i < $strlen - 1) {
			switch(getitem(infix, {i + 1, infix.size()}) {
						case "\r\n":
						case "\n":
						break;
						default:
						throw std::runtime_error("illegal characters after ReverseSolidus: " + getitem(infix, {i, infix.size()}));
					}
				}

				state["ReverseSolidus"] = true;
				break;
			case ']':
				caret = caret->parent->append_right_bracket();
				break;

			case '^':
				if (i + 1 < $strlen && infix[i + 1] == '=') {
					++i;
					$class = "ExclusiveOrAssignment";
				} else
					$class = "ExclusiveOr";

				caret = caret->parent->append_binary_operator($class, caret);
				break;

			case '_':
				append_identifier(caret, infix, i);
				break;
			case '`':
				// unicodedata.name('`')
				caret = caret->append_GraveAccent();
				break;
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
			case 'g':
			case 'h':
			case 'i':
			case 'j':
			case 'k':
			case 'l':
			case 'm':
			case 'n':
			case 'o':
			case 'p':
			case 'q':
			case 'r':
			case 's':
			case 't':
			case 'u':
			case 'v':
			case 'w':
			case 'x':
			case 'y':
			case 'z':
				append_identifier(caret, infix, i);
				break;

			case '{':
				caret = caret->append_left_brace();
				break;

			case '|':
				if (i + 1 < $strlen && infix[i + 1] == "=") {
					++i;
					$class = "BitwiseOrAssignment";
				} else
					$class = "BitwiseOr";

				caret = caret->parent->append_binary_operator($class, caret);
				break;
			case '}':
				caret = caret->parent->append_right_brace();
				break;

			case '~':
				caret = caret->append_unary_operator<Invert>();
				break;
			default:
				if (ord(ch) >= 128) {
					append_identifier(caret, infix, i);
				} else {
					print("unrecognized character: " + ord(ch));
				}

				break;
			}
		}

		return caret;
	}

	PyObject* fetch_whole_sentence(PyObject *caret) {
		for (;;) {
			if (caret->parent != nullptr)
				caret = caret->parent;
			else
				break;
		}
		return caret;
	}

	int len_args(const string &statement, PyObject *caret = nullptr) {
		CompilerState state;

		caret = compile(statement, state, caret);
		if (state) {
			if (array_key_exists('ReverseSolidus', state)) {
//             statement = substr(statement, 0, - 1);
				unset(state['ReverseSolidus']);
				return caret;
			}

			if (array_key_exists('commentStart', state)) {
//             commentStart = state['commentStart'];
//             charDeleted = $strlen(line) - commentStart;
//             statement = substr(statement, 0, - charDeleted);
				unset(state['commentStart']);
				return caret;
			}
		}

		if (([](PyObject *self) -> bool {
			for (;;) {
				auto parent = self->parent;
				if (is_unfinished(parent, self)) {
					return true;
				}
				self = parent;
				if (parent == nullptr) {
					return false;
				}
			}
		})(caret)) {
			return caret;
		}

		auto sentence = fetch_whole_sentence(caret);
		caret = sentence->args[0];

		if (caret->instanceof<Comma>() || caret->instanceof<ArrayList>()
				|| caret->instanceof<Tuple>()) {
			int count = caret->args.size();
			auto last = caret->args.back();
			if (last->instanceof<Caret>()) {
				--count;
			}

		}

		return 1;
	}

	bool is_unfinished(PyObject *parent, PyObject *self) {
		if (parent->instanceof<FunctionCall>() || //
				parent->instanceof<ArrayList>() || //
				parent->instanceof<Tuple>() || //
				parent->instanceof<Parenthesis>() || //
				parent->instanceof<Indexed>() || //
				parent->instanceof<Set>())
			return true;

		if (parent->instanceof<IfElse>()) {
			return self != ((IfElse*) parent)->other;
		}

		return false;
	}

//int main(int offset = 0)
//{
//    // py = "All(Any(cond._subs(x, y), *limits_e), *limits_f)";
//    // offset = 0;
//    count = 0;
//    caret = null;
//    folder = dirname(dirname(dirname(__file__)));
//    // folder = 'D:\Program Files\Python36";
//    // folder = dirname(dirname(__file__));
//    // folder = dirname(__file__);
//    foreach (\std\list_all_files(folder, 'py') as py) {
//
//        // \std\println("processing:\n" . py);
//        try {
//            py = new \std\Text(py);
//        } catch (std::exception e) {
//            continue;
//        }
//
//        paragraphCommentDoubleQuote = false;
//        paragraphCommentSingleQuote = false;
//        // history = [];
//        foreach (py as line) {
//            // history[] = line;
//            comment = false;
//            if (! preg_match('/""".*"""/', line, m) && preg_match('/"""/', line, m)) {
//                paragraphCommentDoubleQuote = ! paragraphCommentDoubleQuote;
//                comment = true;
//            }
//
//            if (! preg_match("/'''.*'''/", line, m) && preg_match("/'''/", line, m)) {
//                paragraphCommentSingleQuote = ! paragraphCommentSingleQuote;
//                comment = true;
//            }
//
//            if (caret === null) {
//                if (preg_match('/^ +return(?=\W) *(.+)/', line, m)) {
//                    // \std\println(line);
//                    ++ count;
//
//                    if (count + 1 <= offset)
//                        continue;
//
//                    statement = m[1];
//
//                    line = statement;
//                } else
//                    continue;
//            } else {
//
//                statement .= line;
//            }
//
//            if (paragraphCommentDoubleQuote || paragraphCommentSingleQuote || comment) {
//                continue;
//            }
//
//            \std\println(statement);
//
//            try {
//                caret = compile(line, state, caret);
//            } catch (std::exception e) {
//                \std\println(e->getMessage());
//                \std\println("count = " . count);
//                \std\println(statement);
//                caret = null;
//                caret = compile(line, state, caret);
//
//                nodeString = (string) caret;
//
//                \std\println(nodeString);
//                throw e;
//            }
//
//            if (state) {
//                if (array_key_exists('ReverseSolidus', state)) {
//                    statement = substr(statement, 0, - 1);
//                    unset(state['ReverseSolidus']);
//                    continue;
//                }
//
//                if (array_key_exists('commentStart', state)) {
//                    commentStart = state['commentStart'];
//                    charDeleted = $strlen(line) - commentStart;
//                    statement = substr(statement, 0, - charDeleted);
//                    unset(state['commentStart']);
//                }
//            }
//
//            if ((function (self) {
//                for (;;) {
//                    parent = self->parent;
//                    if (is_unfinished(parent, self)) {
//                        return true;
//                    }
//                    self = parent;
//                    if (parent === null) {
//                        return false;
//                    }
//                }
//            })(caret)) {
//                continue;
//            }
//
//            nodeString = (string) fetch_whole_sentence(caret);
//            if (! \std\equals(str_replace(' ', '', nodeString), str_replace(' ', '', statement))) {
//                \std\println("count = " . count);
//                \std\println("caret = " . caret);
//                \std\println("original    = " . statement);
//                \std\println("transformed = " . nodeString);
//                throw std::runtime_error("mismatch detected");
//            }
//            caret = null;
//        }
//    }
//
//    \std\println("count = " . count);
//}

