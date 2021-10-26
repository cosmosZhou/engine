#pragma once

struct Sentence : PyObject
{

    static function input_precedence()
    {
        return 0;
    }

    static function stack_precedence()
    {
        return 0;
    }

    function __construct($args)
    {
        $this->args = $args;
        foreach ($args as $arg) {
            $arg->parent = $this;
        }
    }

    function append_left_brace()
    {
        $caret = new Caret();
        $this->args[] = new Set($caret, $this);
        return $caret;
    }

    function append_left_parenthesis()
    {
        $caret = new Caret();
        $this->args[] = new Set($caret, $this);
        return $caret;
    }

    function append_identifier($name)
    {
        $parent = $this->parent;
        $suffix = new TreeNodeSuffix($identifier, $this, $parent);
        $parent->replace($this, $suffix);

        return $suffix;
    }

    $args;

    function toString()
    {
        return implode("; ", array_map(fn ($node) => $node->toString(), $this->args));
    }

    function replace($old, $new)
    {
        $i = array_search($old, $this->args, true);
        if ($i === false)
            throw new std::exception("void replace(TreeNode old, TreeNode replacement) throws Exception");
        $this->args[$i] = $new;
    }

    function append_comma($child)
    {
        $obj = end($this->args);
        assert($obj == $child);

        $caret = new Caret();
        $comma = new Comma([
            $obj,
            $caret
        ], $this);
        $this->replace($obj, $comma);
        return $caret;
    }

    function append_semicolon($child)
    {
        $caret = new Caret($this);
        $this->args[] = $caret;
        return $caret;
    }
}
;
