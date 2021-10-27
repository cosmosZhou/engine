// as in the form: i async for i in (1, 2, 3)
#pragma once

struct GeneratorAsync : Generator
{

    static function input_precedence()
    {
        return 0;
    }

    static function stack_precedence()
    {
        return 0;
    }

    function __construct($expr, $var, $domain, $parent)
    {
        parent::__construct($expr, $var, $domain, $parent);
    }

    string toString()
    {
        return "$this->expr async for $this->var in $this->domain";
    }
}
;
