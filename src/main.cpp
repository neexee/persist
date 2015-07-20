#include "parray.h"
#include "plist.h"
#include "putil.h"
#include <iostream>

int main(void) {
	persist::parray<int, 2> array = {1, 2};
	array.update(1, 4);
	std::cout << array << std::endl;
	persist::list<int> list = {5, 6, 7, 8};
	std::cout << list << std::endl;
	auto it = std::next(list.cbegin(), 2);
	list.insert(it, 100);
	std::cout << list << std::endl;
}
