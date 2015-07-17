#include "parray.h"
#include "putil.h"
#include <iostream>

int main(void) {
	persist::parray<int, 2> array;
	array.update(1, 4);
	std::cout << array << std::endl;
}
