// as in the form: i async for i in (1, 2, 3) if i
#pragma once

struct GeneratorAsyncIf : GeneratorAsync
{

    static function input_precedence()
    {
        return 0;
    }

    static function stack_precedence()
    {
        return 0;
    }

    protected $cond;

    function __construct($expr, $var, $domain, $cond, $parent)
    {
        parent::__construct($expr, $var, $domain, $parent);
        $this->cond = $cond;

        $cond->parent = $this;
    }

    function replace($old, $new)
    {
        if ($old === $this->cond) {
            $this->cond = $new;
        } else {
            parent::replace($old, $new);
        }
    }

    string toString()
    {
        return parent::toString() . " if $this->cond";
    }
}
;
