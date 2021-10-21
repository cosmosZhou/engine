#include "../std/utility.h"

int search_for_identifier(const string &$infix, int $i)
{
    static char $_ = 95; // ord('_');
    static char $a = 97; // ord('a');
    static char $z = 122; // ord('z');

    static char $A = 65; // ord('A');
    static char $Z = 90; // ord('Z');

    static char $_0 = 48; // ord('0');
    static char $_9 = 57; // ord('9');

    $strlen = strlen($infix);
    for (; $i < $strlen; ++ $i) {
        $ch = ord($infix[$i]);
        if ($ch >= $a && $ch <= $z || $ch >= $A && $ch <= $Z || $ch >= $_0 && $ch <= $_9 || $ch == $_) {
            continue;
        } else if ($ch >= 128) {
            $i += TextC::get_utf8_char_len($ch) - 1;
        } else
            return $i;
    }
    return $i;
}

function search_for_digits(&$infix, $i)
{
    static $_0 = 48; // ord('0');
    static $_9 = 57; // ord('9');

    $strlen = strlen($infix);
    if ($infix[$i] == '0') {
        if ($i + 1 < $strlen) {
            switch ($infix[$i + 1]) {
                case 'x':
                case 'X':

                    static $A = 65; // ord('A');
                    static $F = 70; // ord('F');

                    static $a = 97; // ord('a');
                    static $f = 102; // ord('f');

                    $i += 2;
                    for (; $i < $strlen; ++ $i) {
                        $ch = ord($infix[$i]);
                        if ($ch >= $_0 && $ch <= $_9 || $ch >= $a && $ch <= $f || $ch >= $A && $ch <= $F) {
                            continue;
                        } else
                            break;
                    }

                    return $i;
                case 'o':
                case 'O':
                    $i += 2;
                    static $_7 = 55; // ord('7');
                    for (; $i < $strlen; ++ $i) {
                        $ch = ord($infix[$i]);
                        if ($ch >= $_0 && $ch <= $_7) {
                            continue;
                        } else
                            break;
                    }

                    return $i;
            }
        }
    }

    for (; $i < $strlen; ++ $i) {
        $ch = ord($infix[$i]);
        if ($ch >= $_0 && $ch <= $_9) {
            continue;
        }

        switch ($infix[$i]) {
            case 'j':
            case 'J':
                ++ $i;
            default:
                return $i;
            case '.':
                break;
            case 'e':
            case 'E':

                ++ $i;
                switch ($infix[$i]) {
                    case '+':
                    case '-':
                        ++ $i;
                        break;
                    default:
                        break;
                }

                for (; $i < $strlen; ++ $i) {
                    $ch = ord($infix[$i]);
                    if ($ch >= $_0 && $ch <= $_9) {
                        continue;
                    }

                    switch ($infix[$i]) {
                        case 'j':
                        case 'J':
                            ++ $i;
                        default:
                            return $i;
                    }
                }

                break;
        }
    }
    return $i;
}

function search_for_mark(&$infix, $i, $mark)
{
    $strlen = strlen($infix);
    for (++ $i; $i < $strlen; ++ $i) {
        if ($infix[$i] == $mark) {
            if ($infix[$i - 1] == '\\') {
                if ($i >= 2 && $infix[$i - 2] == '\\') {
                    return $i + 1;
                }
            } else
                return $i + 1;
        }
    }
    return $i;
}

function append_identifier(&$caret, &$infix, &$i)
{
    $end = search_for_identifier($infix, $i);

    if ($end == $i) {
        throw new std::exception("lexeme not found!");
    }

    // \std\println(\std\slice($infix, $i, $end));

    $caret = $caret->append_identifier(\std\slice($infix, $i, $end));

    $i = $end - 1;
}

function compile(string &$infix, &$state, $caret = null)
{
    if ($caret === null) {
        $caret = new Caret();
        $sentence = new Sentence([
            $caret
        ]);
    }

    $strlen = strlen($infix);
    for ($i = 0; $i < $strlen; ++ $i) {
        $ch = $infix[$i];
        switch ($ch) {
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
                if ($i + 1 < $strlen && $infix[$i + 1] == '=') {
                    ++ $i;
                    // x != y
                    $caret = $caret->parent->append_binary_operator('python\Unequal', $caret);
                } else {
                    throw new std::exception('illegal character $ch after !');
                }

                break;
            case '"':
                // unicodedata.name('"')
                $caret = $caret->append_literal($infix, $i, $ch);
                break;
            case '#':
                $state['commentStart'] = $i;
                return $caret;
            case '$':
                // unicodedata.name("$")
                $caret = $caret->append_dollarSign();
                break;

            case '%':
                // unicodedata.name("%")
                if ($i + 1 < $strlen && $infix[$i + 1] == '=') {
                    ++ $i;
                    $class = 'python\ModAssignment';
                } else {
                    $class = 'python\Mod';
                }
                $caret = $caret->parent->append_binary_operator($class, $caret);
                break;

            case '&':
                // unicodedata.name("&")
                if ($i + 1 < $strlen && $infix[$i + 1] == '=') {
                    ++ $i;
                    // x &= y
                    $class = 'python\BitwiseAndAssignment';
                } else {
                    // x & y
                    $class = 'python\BitwiseAnd';
                }

                $caret = $caret->parent->append_binary_operator($class, $caret);
                break;

            case "'":
                // unicodedata.name("'")
                $caret = $caret->append_literal($infix, $i, $ch);
                break;
            case '(':
                $caret = $caret->append_left_parenthesis();
                break;
            case ')':
                $caret = $caret->parent->append_right_parenthesis();
                break;

            case '*':
                if ($caret instanceof Caret) {
                    if ($i + 1 < $strlen && $infix[$i + 1] == '*') {
                        ++ $i;
                        // **kwargs
                        $class = 'python\DoubleStar';
                    } else {
                        // **args
                        $class = 'python\Star';
                    }

                    $caret = $caret->append_unary_operator($class);
                } else {
                    if ($i + 1 < $strlen) {

                        switch ($infix[$i + 1]) {
                            case '=':
                                ++ $i;
                                // x *= y
                                $class = 'python\MulAssignment';
                                break;
                            case '*':
                                ++ $i;
                                if ($i + 1 < $strlen && $infix[$i + 1] == '=') {
                                    ++ $i;
                                    // x **= y
                                    $class = 'python\PowAssignment';
                                } else {
                                    $class = 'python\Pow';
                                }

                                break;
                            default:
                                // x * y
                                $class = 'python\Mul';
                                break;
                        }
                    } else {
                        // x * y
                        $class = 'python\Mul';
                    }

                    $caret = $caret->parent->append_binary_operator($class, $caret);
                }

                break;
            case '+':
                if ($caret instanceof Caret) {
                    $caret = $caret->append_unary_operator('python\Plus');
                } else {
                    if ($i + 1 < $strlen && $infix[$i + 1] == '=') {

                        ++ $i;
                        // x += y
                        $class = 'python\AddAssignment';
                    } else {
                        // x + y
                        $class = 'python\Add';
                    }

                    $caret = $caret->parent->append_binary_operator($class, $caret);
                }

                break;
            case ',':
                $caret = $caret->parent->append_comma($caret);
                break;
            case '-':
                if ($caret instanceof Caret) {
                    $caret = $caret->append_unary_operator('python\Neg');
                } else {
                    if ($i + 1 < $strlen && $infix[$i + 1] == '=') {

                        ++ $i;
                        // x -= y
                        $class = 'python\SubAssignment';
                    } else {
                        // x - y
                        $class = 'python\Sub';
                    }

                    $caret = $caret->parent->append_binary_operator($class, $caret);
                }

                break;
            case '.':
                if ($i + 2 < $strlen && \std\equals(substr($infix, $i, 3), '...')) {
                    $i += 2;
                    $caret = $caret->append_ellipsis();
                } else {
                    $caret = $caret->parent->append_binary_operator('python\Dot', $caret);
                }

                break;
            case '/':
                if ($i + 1 < $strlen) {

                    switch ($infix[$i + 1]) {
                        case '=':
                            ++ $i;
                            // x /= y
                            $class = 'python\DivAssignment';
                            break;
                        case '/':
                            ++ $i;
                            if ($i + 1 < $strlen && $infix[$i + 1] == '=') {
                                ++ $i;
                                // x //= y
                                $class = 'python\FloorDivAssignment';
                            } else {
                                // x // y
                                $class = 'python\FloorDiv';
                            }

                            break;
                        default:
                            // x / y
                            $class = 'python\Div';
                            break;
                    }
                } else {
                    // x / y
                    $class = 'python\Div';
                }

                $caret = $caret->parent->append_binary_operator($class, $caret);

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
                $caret = $caret->append_digit($infix, $i);
                break;

            case ':':
                $caret = $caret->parent->append_colon($caret);
                break;

            case ';':
                $caret = $caret->parent->append_semicolon($caret);
                break;

            case '<':
                if ($i + 1 < $strlen) {
                    switch ($infix[$i + 1]) {
                        case '=':
                            ++ $i;
                            // x <= y
                            $class = 'python\LessEqual';
                            break;
                        case '<':
                            ++ $i;
                            if ($i + 1 < $strlen) {
                                switch ($infix[$i + 1]) {
                                    case '=':
                                        ++ $i;
                                        // x <<= y
                                        $class = 'python\LeftShiftAssignment';
                                        break;
                                    default:
                                        // x << y
                                        $class = 'python\LeftShift';
                                        break;
                                }
                            } else {
                                // x << y
                                $class = 'python\LeftShift';
                            }
                            break;
                        default:
                            // x < y
                            $class = 'python\Less';
                            break;
                    }
                }

                $caret = $caret->parent->append_binary_operator($class, $caret);
                break;

            case '=':
                if ($i + 1 < $strlen && $infix[$i + 1] == '=') {
                    ++ $i;
                    // x == y
                    $class = 'python\Equal';
                } else
                    $class = 'python\EqualAssignment';

                $caret = $caret->parent->append_binary_operator($class, $caret);
                break;

            case '>':

                if ($i + 1 < $strlen) {
                    switch ($infix[$i + 1]) {
                        case '=':
                            ++ $i;
                            // x >= y
                            $class = 'python\GreaterEqual';
                            break;
                        case '>':
                            ++ $i;
                            if ($i + 1 < $strlen && $infix[$i + 1] == '=') {
                                ++ $i;
                                // x >>= y
                                $class = 'python\RightShiftAssignment';
                            } else
                                // x >> y
                                $class = 'python\RightShift';
                            break;
                        default:
                            // x > y
                            $class = 'python\Greater';
                            break;
                    }
                } else
                    // x > y
                    $class = 'python\Greater';

                $caret = $caret->parent->append_binary_operator($class, $caret);
                break;

            case '?':
                // unicodedata.name('?')
                $caret = $caret->append_QuestionMark();
                break;
            case '@':
                // unicodedata.name('@')
                if ($i + 1 < $strlen && $infix[$i + 1] == '=') {
                    ++ $i;
                    $class = 'python\MatMulAssignment';
                } else
                    $class = 'python\MatMul';

                $caret = $caret->parent->append_binary_operator($class, $caret);
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
                append_identifier($caret, $infix, $i);

                break;
            case '[':
                $caret = $caret->append_left_bracket();
                break;
            case '\\':
                // unicodedata.name('\\')
                if ($i < $strlen - 1){
                    switch(\std\slice($infix, $i + 1)){
                        case "\r\n":
                        case "\n":
                            break;
                        default:
                            throw new std::exception("illegal characters after ReverseSolidus: " . \std\slice($infix, $i));
                    }
                }

                $state['ReverseSolidus'] = true;
                break;
            case ']':
                $caret = $caret->parent->append_right_bracket();
                break;

            case '^':
                if ($i + 1 < $strlen && $infix[$i + 1] == '=') {
                    ++ $i;
                    $class = 'python\ExclusiveOrAssignment';
                } else
                    $class = 'python\ExclusiveOr';

                $caret = $caret->parent->append_binary_operator($class, $caret);
                break;

            case '_':
                append_identifier($caret, $infix, $i);
                break;
            case '`':
                // unicodedata.name('`')
                $caret = $caret->append_GraveAccent();
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
                append_identifier($caret, $infix, $i);
                break;

            case '{':
                $caret = $caret->append_left_brace();
                break;

            case '|':
                if ($i + 1 < $strlen && $infix[$i + 1] == "=") {
                    ++ $i;
                    $class = 'python\BitwiseOrAssignment';
                } else
                    $class = 'python\BitwiseOr';

                $caret = $caret->parent->append_binary_operator($class, $caret);
                break;
            case '}':
                $caret = $caret->parent->append_right_brace();
                break;

            case '~':
                $caret = $caret->append_unary_operator('python\Invert');
                break;
            default:
                if (ord($ch) >= 128) {
                    append_identifier($caret, $infix, $i);
                } else {
                    \std\println("unrecognized character: " . ord($ch));
                }

                break;
        }
    }

    return $caret;
}

function fetch_whole_sentence($caret)
{
    for (;;) {
        if ($caret->parent !== null)
            $caret = $caret->parent;
        else
            break;
    }
    return $caret;
}

function len_args(&$statement, $caret = null)
{
    // error_log("in " . __function__);
    // error_log("statement = $statement");
    // error_log("caret = $caret");
    $state = [];

    $caret = compile($statement, $state, $caret);
    if ($state) {
        if (array_key_exists('ReverseSolidus', $state)) {
//             $statement = substr($statement, 0, - 1);
            unset($state['ReverseSolidus']);
            return $caret;
        }

        if (array_key_exists('commentStart', $state)) {
//             $commentStart = $state['commentStart'];
//             $charDeleted = strlen($line) - $commentStart;
//             $statement = substr($statement, 0, - $charDeleted);
            unset($state['commentStart']);
            return $caret;
        }
    }

    if ((function ($self) {
        for (;;) {
            $parent = $self->parent;
            if (is_unfinished($parent, $self)) {
                return true;
            }
            $self = $parent;
            if ($parent === null) {
                return false;
            }
        }
    })($caret)) {
        return $caret;
    }

    $sentence = fetch_whole_sentence($caret);
    list ($caret,) = $sentence->args;

    if ($caret instanceof Comma || $caret instanceof ArrayList || $caret instanceof Tuple) {
        $count = count($caret->args);
        $last = end($caret->args);
        if ($last instanceof Caret) {
            -- $count;
        }

        return $count;
    }

    return 1;
}

require_once 'std.php';

function is_unfinished($parent, $self)
{
    if ($parent instanceof FunctionCall || //
    $parent instanceof ArrayList || //
    $parent instanceof Tuple || //
    $parent instanceof Parenthesis || //
    $parent instanceof Indexed || //
    $parent instanceof Set)
        return true;

    if ($parent instanceof IfElse) {
        return $self !== $parent->other;
    }

    return false;
}

function main($offset = 0)
{
    // $py = "All(Any(cond._subs(x, y), *limits_e), *limits_f)";
    // $offset = 0;
    $count = 0;
    $caret = null;
    $folder = dirname(dirname(dirname(__file__)));
    // $folder = 'D:\Program Files\Python\Python36';
    // $folder = dirname(dirname(__file__));
    // $folder = dirname(__file__);
    foreach (\std\list_all_files($folder, 'py') as $py) {

        // \std\println("processing:\n" . $py);
        try {
            $py = new \std\Text($py);
        } catch (std::exception $e) {
            continue;
        }

        $paragraphCommentDoubleQuote = false;
        $paragraphCommentSingleQuote = false;
        // $history = [];
        foreach ($py as $line) {
            // $history[] = $line;
            $comment = false;
            if (! preg_match('/""".*"""/', $line, $m) && preg_match('/"""/', $line, $m)) {
                $paragraphCommentDoubleQuote = ! $paragraphCommentDoubleQuote;
                $comment = true;
            }

            if (! preg_match("/'''.*'''/", $line, $m) && preg_match("/'''/", $line, $m)) {
                $paragraphCommentSingleQuote = ! $paragraphCommentSingleQuote;
                $comment = true;
            }

            if ($caret === null) {
                if (preg_match('/^ +return(?=\W) *(.+)/', $line, $m)) {
                    // \std\println($line);
                    ++ $count;

                    if ($count + 1 <= $offset)
                        continue;

                    $statement = $m[1];

                    $line = $statement;
                } else
                    continue;
            } else {

                $statement .= $line;
            }

            if ($paragraphCommentDoubleQuote || $paragraphCommentSingleQuote || $comment) {
                continue;
            }

            \std\println($statement);

            try {
                $caret = compile($line, $state, $caret);
            } catch (std::exception $e) {
                \std\println($e->getMessage());
                \std\println("count = " . $count);
                \std\println($statement);
                $caret = null;
                $caret = compile($line, $state, $caret);

                $nodeString = (string) $caret;

                \std\println($nodeString);
                throw $e;
            }

            if ($state) {
                if (array_key_exists('ReverseSolidus', $state)) {
                    $statement = substr($statement, 0, - 1);
                    unset($state['ReverseSolidus']);
                    continue;
                }

                if (array_key_exists('commentStart', $state)) {
                    $commentStart = $state['commentStart'];
                    $charDeleted = strlen($line) - $commentStart;
                    $statement = substr($statement, 0, - $charDeleted);
                    unset($state['commentStart']);
                }
            }

            if ((function ($self) {
                for (;;) {
                    $parent = $self->parent;
                    if (is_unfinished($parent, $self)) {
                        return true;
                    }
                    $self = $parent;
                    if ($parent === null) {
                        return false;
                    }
                }
            })($caret)) {
                continue;
            }

            $nodeString = (string) fetch_whole_sentence($caret);
            if (! \std\equals(str_replace(' ', '', $nodeString), str_replace(' ', '', $statement))) {
                \std\println("count = " . $count);
                \std\println("caret = " . $caret);
                \std\println("original    = " . $statement);
                \std\println("transformed = " . $nodeString);
                throw new std::exception("mismatch detected");
            }
            $caret = null;
        }
    }

    \std\println("count = " . $count);
}

