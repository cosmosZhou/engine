// as in the form: return (yield x)
#pragma once

struct GeneratorYieldFrom : UnaryOperator
{
	__declare_common_interface(0, 0);

    string toString()
    {
        return "yield from $this->arg";
    }
}
;
