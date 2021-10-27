// as in the form: return (yield x)
#pragma once

struct GeneratorYield : UnaryOperator
{
	__declare_common_interface(0, 0);

    string toString()
    {
        return "yield $this->arg";
    }
}
;
