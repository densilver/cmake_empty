#include <cstdint>
#include <limits>

#include <iostream>

static void test() {
	std::uint32_t n = std::numeric_limits<std::uint32_t>::max();
	n += 1;
	int *p = new int[n];
	std::cout << "p: " << p << "\n";
}

int main() {
	test();
}
