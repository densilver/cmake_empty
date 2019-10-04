#include <cstdint>
#include <limits>

#include <iostream>

static void test() {
	constexpr unsigned int psz = sizeof(void *);
	constexpr auto n = std::numeric_limits<std::uint64_t>::max() / (1ull << (psz == 4 ? 32 : 3));

	char* p = new(std::nothrow) char[n];
	std::cout << "psz: " << psz << "\n";
	std::cout << "n: " << n << "\n";
	std::cout << "p: " << static_cast<void *>(p) << "\n";
}

int main() {
	test();
}
