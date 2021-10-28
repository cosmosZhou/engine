#pragma once
#include "PyObject.h"
struct Literal : PyObject
{
	__declare_common_interface(0, 11);

    PyObject *$literal;

    function __construct(string $literal, $parent = null)
    {
        $this->literal = $literal;
        $this->parent = $parent;
    }

    string toString()
    {
        return $this->literal;
    }

    static function is_literal_prefix($literal)
    {
        switch ($literal) {
            case 'r':
            case 'f':
            case 'u':
            case 'b':
            case 'R':
            case 'F':
            case 'U':
            case 'B':

            case 'rf':
            case 'rb':
            case 'rF':
            case 'rB':

            case 'Rf':
            case 'Rb':
            case 'RF':
            case 'RB':

            case 'fr':
            case 'br':
            case 'Fr':
            case 'Br':

            case 'fR':
            case 'bR':
            case 'FR':
            case 'BR':
                return true;
            default:
                return false;
        }
    }

    function append_literal(&$infix, &$i, $mark)
    {
        $end = search_for_mark($infix, $i, $mark);

        if ($end == $i) {
            throw std::runtime_error("literal not found!");
        }

        $string = \std\slice($infix, $i, $end);

        $parent = $this->parent;
        if ($parent instanceof Literals) {

            if (Literal::is_literal_prefix($this->literal)) {

                $this->literal .= $string;
                $caret = $this;
            } else {
                $caret = new Literal($string, $parent);
                $parent->args[] = $caret;
            }
        } else {
            $caret = new Literal($string);
            $new = new Literals([
                $this,
                $caret
            ], $parent);

            $parent->replace($this, $new);
        }

        $i = $end - 1;
        return $caret;
    }
}
;
