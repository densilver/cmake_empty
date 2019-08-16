#include <cstdint>
#include <limits>

#include <iostream>

static void test() {
	constexpr auto n = std::numeric_limits<std::uint64_t>::max() / 8;
	auto p = new(std::nothrow) char8_t[n];
	std::cout << "p: " << p << "\n";
}

int main() {
	test();
}
