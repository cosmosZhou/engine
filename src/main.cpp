#include <time.h>
#include <string>
#include <iostream>
using namespace std;

#include <stdio.h>

#include<iostream>
#include "std/utility.h"
#include "python/PyObject.h"

int main(int argc, char **argv) {
//    int count = 0;
//    PyObject *caret = nullptr;

    string py = argv[1];

	auto file = TextC(py);

//	auto $paragraphCommentDoubleQuote = false;
//	auto $paragraphCommentSingleQuote = false;
	// $history = [];
	for (auto &line : file) {
		// $history[] = $line;
		print(line);
//		auto $comment = false;
//		if (! preg_match('/""".*"""/', $line, $m) && preg_match('/"""/', $line, $m)) {
//			$paragraphCommentDoubleQuote = ! $paragraphCommentDoubleQuote;
//			$comment = true;
//		}

//		if (! preg_match("/'''.*'''/", $line, $m) && preg_match("/'''/", $line, $m)) {
//			$paragraphCommentSingleQuote = ! $paragraphCommentSingleQuote;
//			$comment = true;
//		}

//		if (!$caret) {
//			if (preg_match('/^ +return(?=\W) *(.+)/', $line, $m)) {
//				// \std\println($line);
//				++ $count;
//
//				if ($count + 1 <= $offset)
//					continue;
//
//				$statement = $m[1];
//
//				$line = $statement;
//			} else
//				continue;
//		} else {
//
//			$statement .= $line;
//		}
//
//		if ($paragraphCommentDoubleQuote || $paragraphCommentSingleQuote || $comment) {
//			continue;
//		}
//
//		\std\println($statement);
//
//		try {
//			$caret = compile($line, $state, $caret);
//		} catch (std::exception $e) {
//			\std\println($e->getMessage());
//			\std\println("count = " . $count);
//			\std\println($statement);
//			$caret = null;
//			$caret = compile($line, $state, $caret);
//
//			$nodeString = (string) $caret;
//
//			\std\println($nodeString);
//			throw $e;
//		}
//
//		if ($state) {
//			if (array_key_exists('ReverseSolidus', $state)) {
//				$statement = substr($statement, 0, - 1);
//				unset($state['ReverseSolidus']);
//				continue;
//			}
//
//			if (array_key_exists('commentStart', $state)) {
//				$commentStart = $state['commentStart'];
//				$charDeleted = strlen($line) - $commentStart;
//				$statement = substr($statement, 0, - $charDeleted);
//				unset($state['commentStart']);
//			}
//		}
//
//		if ((function ($self) {
//			for (;;) {
//				$parent = $self->parent;
//				if (is_unfinished($parent, $self)) {
//					return true;
//				}
//				$self = $parent;
//				if ($parent === null) {
//					return false;
//				}
//			}
//		})($caret)) {
//			continue;
//		}
//
//		$nodeString = (string) fetch_whole_sentence($caret);
//		if (! \std\equals(str_replace(' ', '', $nodeString), str_replace(' ', '', $statement))) {
//			\std\println("count = " . $count);
//			\std\println("caret = " . $caret);
//			\std\println("original    = " . $statement);
//			\std\println("transformed = " . $nodeString);
//			throw std::runtime_error("mismatch detected");
//		}
//		$caret = null;
	}
//
//    \std\println("count = " . $count);
    return 0;
}

// main();

