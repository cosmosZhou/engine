#include <time.h>
#include <string>
#include <iostream>
using namespace std;


#include <stdio.h>

#include<iostream>
#include "std/utility.h"
#include "python/PyObject.h"

int main(int argc, char **argv) {
{
    // $py = "All(Any(cond._subs(x, y), *limits_e), *limits_f)";
    // $offset = 0;
    int $count = 0;
    PyObject *caret = nullptr;
    $folder = dirname(dirname(dirname(__file__)));
    // $folder = 'D:\Program Files\Python\Python36';
    // $folder = dirname(dirname(__file__));
    // $folder = dirname(__file__);
    string py = argv[1];

	// \std\println("processing:\n" . $py);
	try {
		$py = new \std\Text($py);
	} catch (RuntimeException $e) {
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
		} catch (RuntimeException $e) {
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
			throw new RuntimeException("mismatch detected");
		}
		$caret = null;
	}

    \std\println("count = " . $count);
    return 0;
}

// main();

