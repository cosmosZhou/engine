#include <string>
#include <vector>
using std::vector;

using String = std::u16string;
#include<iomanip>
#include <iostream>
#define __print(symbol) std::cout << #symbol << " = " << (symbol) << std::endl;

extern "C" {

int ahocorasick_ner_en(int text) {
	__print(__PRETTY_FUNCTION__);
	__print(text);
	return text + 1;
}

}

