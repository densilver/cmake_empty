#include "matcher.h"

#include <iostream>
#include <string>

using namespace Matcher;

struct Delegate : public CLogReader::Delegate {
	void OnMatchFound(const char* block, std::size_t block_size) override {
		std::string s(block, block+block_size);
		std::cout << s;
	}
};

int main() {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	if (!reader.SetFilter("*a")) {
		return 1;
	}
	std::string s = "d";
	reader.AddSourceBlock(s.c_str(), s.length());
	s = "d";
	reader.AddSourceBlock(s.c_str(), s.length());
	s = "a";
	reader.AddSourceBlock(s.c_str(), s.length());
	s = "\n";
	reader.AddSourceBlock(s.c_str(), s.length());
	return 0;
}
