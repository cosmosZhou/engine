// as in the form: i async for i in (1, 2, 3)
#pragma once
#include "Generator.h"
struct GeneratorAsync : Generator
{
	__declare_common_interface(0, 0);

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
