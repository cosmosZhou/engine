int search_for_identifier(const string &$infix, int $i);

int search_for_digits(const string &$infix, int $i);

int search_for_mark(const string &$infix, int $i, char $mark);

void append_identifier(PyObject *&caret, const string &$infix, int &$i);


struct CompilerState{
	bool ReverseSolidus;
	bool commentStart;
};

PyObject *compile(const string &$infix, CompilerState &state, PyObject *caret = nullptr);

PyObject *fetch_whole_sentence(PyObject *caret);

int len_args(const string &statement, PyObject *caret = nullptr);

bool is_unfinished(PyObject *parent, PyObject *self);

