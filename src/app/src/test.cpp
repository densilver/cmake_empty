#define CATCH_CONFIG_MAIN

#include "catch/catch.hpp"

#include "matcher.h"

#include <vector>
#include <string>

using namespace Matcher;

using matches_list = std::vector<std::string>;

struct Delegate : public CLogReader::Delegate {
	void OnMatchFound(const char* block, std::size_t block_size) override {
		if (matches.empty()) {
			AddLine(block, block_size);
			return;
		}

		auto& last = matches[matches.size()-1];
		if (std::find(last.begin(), last.end(), '\n') != last.end()) {
			AddLine(block, block_size);
			return;
		}

		last += std::string(block, block + block_size);
	}

	void AddLine(const char* block, std::size_t block_size) {
		matches.emplace_back(std::string(block, block + block_size));
	}

	matches_list matches;
};

TEST_CASE("no filter") {
	CLogReader reader;
	REQUIRE(reader.SetFilter(nullptr) == false);
	REQUIRE(reader.AddSourceBlock(nullptr, 0) == false);
	REQUIRE(reader.AddSourceBlock("", 1) == false);
}

TEST_CASE("no block") {
	CLogReader reader;
	REQUIRE(reader.SetFilter("abc") == true);
	REQUIRE(reader.AddSourceBlock(nullptr, 0) == false);
	REQUIRE(reader.AddSourceBlock(nullptr, 1) == false);
}

TEST_CASE("empty block") {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	REQUIRE(reader.SetFilter("abc") == true);
	REQUIRE(reader.AddSourceBlock("", 0) == true);
	REQUIRE(delegate.matches.empty() == true);
}

TEST_CASE("block size less than filter size") {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	REQUIRE(reader.SetFilter("abc") == true);
	REQUIRE(reader.AddSourceBlock("ab", 2) == true);
	REQUIRE(delegate.matches.empty() == true);
}

TEST_CASE("exact match, no new line") {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	REQUIRE(reader.SetFilter("abc") == true);
	REQUIRE(reader.AddSourceBlock("abc", 3) == true);
	REQUIRE(delegate.matches.empty() == true);
}

TEST_CASE("exact match") {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	REQUIRE(reader.SetFilter("abc") == true);
	REQUIRE(reader.AddSourceBlock("abc\n", 4) == true);
	REQUIRE(delegate.matches == matches_list{ "abc\n" });
}

TEST_CASE("match is failed at the start of the line") {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	REQUIRE(reader.SetFilter("abc") == true);
	REQUIRE(reader.AddSourceBlock("_abc\n", 5) == true);
	REQUIRE(delegate.matches == matches_list{});
}

TEST_CASE("match is failed at the end of the line") {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	REQUIRE(reader.SetFilter("abc") == true);
	REQUIRE(reader.AddSourceBlock("abc_\n", 5) == true);
	REQUIRE(delegate.matches == matches_list{});
}

TEST_CASE("two exact matches") {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	REQUIRE(reader.SetFilter("abc") == true);
	REQUIRE(reader.AddSourceBlock("abc\nabc\n", 4+4) == true);
	REQUIRE(delegate.matches == matches_list{ "abc\n", "abc\n" });
}

TEST_CASE("two no matches") {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	REQUIRE(reader.SetFilter("abc") == true);
	REQUIRE(reader.AddSourceBlock("_abc\n_abc\n", 10) == true);
	REQUIRE(delegate.matches == matches_list{});
}

TEST_CASE("match, no match") {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	REQUIRE(reader.SetFilter("abc") == true);
	REQUIRE(reader.AddSourceBlock("abc\n_abc\n", 9) == true);
	REQUIRE(delegate.matches == matches_list{ "abc\n" });
}

TEST_CASE("no match, match") {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	REQUIRE(reader.SetFilter("abc") == true);
	REQUIRE(reader.AddSourceBlock("_abc\nabc\n", 9) == true);
	REQUIRE(delegate.matches == matches_list{ "abc\n" });
}

TEST_CASE("no match, no match without new line") {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	REQUIRE(reader.SetFilter("abc") == true);
	REQUIRE(reader.AddSourceBlock("_abc\n_ab", 8) == true);
	REQUIRE(delegate.matches == matches_list{});
}

TEST_CASE("exact match, new line in the second block") {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	REQUIRE(reader.SetFilter("abc") == true);
	REQUIRE(reader.AddSourceBlock("abc", 3) == true);
	REQUIRE(reader.AddSourceBlock("\n", 1) == true);
	REQUIRE(delegate.matches == matches_list{ "abc\n" });
}

TEST_CASE("match in many blocks") {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	REQUIRE(reader.SetFilter("abc") == true);
	REQUIRE(reader.AddSourceBlock("a", 1) == true);
	REQUIRE(reader.AddSourceBlock("b", 1) == true);
	REQUIRE(reader.AddSourceBlock("c", 1) == true);
	REQUIRE(reader.AddSourceBlock("\n", 1) == true);
	REQUIRE(delegate.matches == matches_list{ "abc\n" });
}

TEST_CASE("no match, match in many blocks") {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	REQUIRE(reader.SetFilter("abc") == true);
	REQUIRE(reader.AddSourceBlock("d", 1) == true);
	REQUIRE(reader.AddSourceBlock("d", 1) == true);
	REQUIRE(reader.AddSourceBlock("\n", 1) == true);
	REQUIRE(reader.AddSourceBlock("a", 1) == true);
	REQUIRE(reader.AddSourceBlock("b", 1) == true);
	REQUIRE(reader.AddSourceBlock("c", 1) == true);
	REQUIRE(reader.AddSourceBlock("\n", 1) == true);
	REQUIRE(delegate.matches == matches_list{ "abc\n" });
}

TEST_CASE("match any symbol") {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	REQUIRE(reader.SetFilter("abc?") == true);
	REQUIRE(reader.AddSourceBlock("abcd\n", 5) == true);
	REQUIRE(delegate.matches == matches_list{ "abcd\n" });
}


TEST_CASE("no match any symbol") {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	REQUIRE(reader.SetFilter("?c?") == true);
	REQUIRE(reader.AddSourceBlock("abc\n", 4) == true);
	REQUIRE(delegate.matches == matches_list{});
}

TEST_CASE("match star") {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	REQUIRE(reader.SetFilter("*") == true);
	REQUIRE(reader.AddSourceBlock("abc\n", 4) == true);
	REQUIRE(delegate.matches == matches_list{"abc\n"});
}

TEST_CASE("match star and any symbol") {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	REQUIRE(reader.SetFilter("?*?") == true);
	REQUIRE(reader.AddSourceBlock("abc\n", 4) == true);
	REQUIRE(delegate.matches == matches_list{"abc\n"});
}

TEST_CASE("match star empty") {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	REQUIRE(reader.SetFilter("*") == true);
	REQUIRE(reader.AddSourceBlock("\n", 1) == true);
	REQUIRE(delegate.matches == matches_list{"\n"});
}

TEST_CASE("match star at the start of the line") {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	REQUIRE(reader.SetFilter("*abc") == true);
	REQUIRE(reader.AddSourceBlock("ddabc\n", 6) == true);
	REQUIRE(delegate.matches == matches_list{"ddabc\n"});
}

TEST_CASE("no match star at the start of the line") {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	REQUIRE(reader.SetFilter("*abc") == true);
	REQUIRE(reader.AddSourceBlock("ddabd\n", 6) == true);
	REQUIRE(delegate.matches == matches_list{});
}

TEST_CASE("match star at the end of the line") {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	REQUIRE(reader.SetFilter("abc*") == true);
	REQUIRE(reader.AddSourceBlock("abcdd\n", 6) == true);
	REQUIRE(delegate.matches == matches_list{"abcdd\n"});
}

TEST_CASE("no match star at the end of the line") {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	REQUIRE(reader.SetFilter("abc*") == true);
	REQUIRE(reader.AddSourceBlock("abdd\n", 5) == true);
	REQUIRE(delegate.matches == matches_list{});
}

TEST_CASE("match star at the start and at the end of the line") {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	REQUIRE(reader.SetFilter("*abc*") == true);
	REQUIRE(reader.AddSourceBlock("ddabcdd\n", 8) == true);
	REQUIRE(delegate.matches == matches_list{"ddabcdd\n"});
}

TEST_CASE("no match star at the start and at the end of the line") {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	REQUIRE(reader.SetFilter("*ac*") == true);
	REQUIRE(reader.AddSourceBlock("ddabcdd\n", 8) == true);
	REQUIRE(delegate.matches == matches_list{});
}

TEST_CASE("long match star") {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	REQUIRE(reader.SetFilter("*a*b*c*") == true);
	REQUIRE(reader.AddSourceBlock("dddadddbdddcddd\n", 16) == true);
	REQUIRE(delegate.matches == matches_list{"dddadddbdddcddd\n"});
}

TEST_CASE("long no match star") {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	REQUIRE(reader.SetFilter("*a*b*c*") == true);
	REQUIRE(reader.AddSourceBlock("dddadddEdddcddd\n", 15) == true);
	REQUIRE(delegate.matches == matches_list{});
}

TEST_CASE("match star in many blocks 1") {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	REQUIRE(reader.SetFilter("*") == true);
	REQUIRE(reader.AddSourceBlock("a", 1) == true);
	REQUIRE(reader.AddSourceBlock("b", 1) == true);
	REQUIRE(reader.AddSourceBlock("c", 1) == true);
	REQUIRE(reader.AddSourceBlock("\n", 1) == true);
	REQUIRE(delegate.matches == matches_list{"abc\n"});
}

TEST_CASE("match star in many blocks 2") {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	REQUIRE(reader.SetFilter("*a") == true);
	REQUIRE(reader.AddSourceBlock("d", 1) == true);
	REQUIRE(reader.AddSourceBlock("d", 1) == true);
	REQUIRE(reader.AddSourceBlock("a", 1) == true);
	REQUIRE(reader.AddSourceBlock("\n", 1) == true);
	REQUIRE(delegate.matches == matches_list{"dda\n"});
}

TEST_CASE("match star in many blocks 3") {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	REQUIRE(reader.SetFilter("a*") == true);
	REQUIRE(reader.AddSourceBlock("a", 1) == true);
	REQUIRE(reader.AddSourceBlock("d", 1) == true);
	REQUIRE(reader.AddSourceBlock("d", 1) == true);
	REQUIRE(reader.AddSourceBlock("\n", 1) == true);
	REQUIRE(delegate.matches == matches_list{"add\n"});
}

TEST_CASE("match star in many blocks 4") {
	CLogReader reader;
	Delegate delegate;
	reader.SetDelegate(&delegate);

	REQUIRE(reader.SetFilter("*a*") == true);
	REQUIRE(reader.AddSourceBlock("d", 1) == true);
	REQUIRE(reader.AddSourceBlock("d", 1) == true);
	REQUIRE(reader.AddSourceBlock("a", 1) == true);
	REQUIRE(reader.AddSourceBlock("d", 1) == true);
	REQUIRE(reader.AddSourceBlock("d", 1) == true);
	REQUIRE(reader.AddSourceBlock("\n", 1) == true);
	REQUIRE(delegate.matches == matches_list{"ddadd\n"});
}