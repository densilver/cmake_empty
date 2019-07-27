#include "matcher.h"

namespace Matcher {

	constexpr std::size_t NotFound = -1;
	constexpr char LineDelimiter = '\n';

	CLogReader::CLogReader()
	: m_filter(nullptr)
	, m_cur_filter(nullptr)
	{
	}

	CLogReader::~CLogReader() {
		ClearPendingBlocks();
	}

	bool CLogReader::SetFilter(const char *filter) {
		m_filter = filter;
		m_cur_filter = m_filter;
		return m_filter != nullptr;
	}

	bool CLogReader::AddSourceBlock(const char *block, const std::size_t block_size) {
		if (!m_cur_filter || !block) {
			return false;
		}

		auto cur_block = block;
		auto cur_block_size = block_size;

		do {
			std::size_t processed_size = 0;

			auto status = Match(cur_block, cur_block_size, processed_size);
			switch (status) {
				case HasMatch: {
					auto tail_size = cur_block_size - processed_size;
					auto i = FindEndOfLine(cur_block + processed_size, tail_size);
					if (i != NotFound) {
						m_cur_filter = m_filter;
						processed_size += i + 1;
						if (i == 0) {
							OnMatchFound(cur_block, processed_size);
						}
					} else {
						processed_size += tail_size;
					}
					break;
				}
				case HasNoMatch: {
					auto tail_size = cur_block_size - processed_size;
					auto i = FindEndOfLine(cur_block + processed_size, tail_size);
					if (i != NotFound) {
						m_cur_filter = m_filter;
						processed_size += i + 1;
					} else {
						processed_size += tail_size;
					}
					OnNoMatchFound();

					break;
				}
				case Pending: {
					if (!AddPendingBlock(cur_block, processed_size)) {
						return false;
					}
					break;
				}
			}

			cur_block += processed_size;
			cur_block_size -= processed_size;
		} while (cur_block_size != 0);

		return true;
	}

	CLogReader::MatchStatus CLogReader::Match(const char *block,
						  std::size_t block_size,
						  std::size_t& processed_size)
	{
		while (block_size != 0) {
			if (m_cur_filter[0] == '\0') {
				return HasMatch;
			}
			if (m_cur_filter[0] == '*') {
				auto filter = m_cur_filter;
				++m_cur_filter;
				auto status = MatchStar(block, block_size, processed_size);
				if (status == Pending) {
					if (filter+1 == m_cur_filter) {
						--m_cur_filter;
					}
				}
				return status;
			}
			if (block[0] == '\n') {
				return HasNoMatch;
			}
			if (m_cur_filter[0] == '?' || m_cur_filter[0] == block[0]) {
				++m_cur_filter;
				++processed_size;
				++block;
				--block_size;
			} else {
				return HasNoMatch;
			}
		}

		return Pending;
	}

	CLogReader::MatchStatus CLogReader::MatchStar(const char *block,
						std::size_t block_size,
						std::size_t& processed_size)
	{
		size_t cur_processed_size = 0;
		do {
			auto filter = m_cur_filter;
			auto status = Match(block + cur_processed_size, block_size, cur_processed_size);
			if (status == HasMatch) {
				processed_size += cur_processed_size;
				auto tail_size = block_size - cur_processed_size;
				auto i = FindEndOfLine(block + cur_processed_size, tail_size);
				if (i != NotFound) {
					processed_size += i;
					return HasMatch;
				}

				processed_size += tail_size;
				return Pending;
			} else if (status == Pending) {
				processed_size += cur_processed_size;
				return Pending;
			} else if (filter != m_cur_filter) {
				break;
			}
		} while (block_size-- != 0 && block[cur_processed_size++] != LineDelimiter);

		processed_size += cur_processed_size;
		return HasNoMatch;
	}

	std::size_t CLogReader::FindEndOfLine(const char* block, const std::size_t block_size) {
		bool found = false;
		size_t i = 0;
		for (; i < block_size; ++i) {
			if (block[i] == LineDelimiter) {
				found = true;
				break;
			}
		}
		return found ? i : NotFound;
	}

	void CLogReader::SetDelegate(Delegate* delegate) {
		m_delegate = delegate;
	}

	void CLogReader::OnMatchFound(const char* block, const std::size_t block_size) {
		if (!m_delegate) {
			ClearPendingBlocks();
			return;
		}

		for (auto v : m_pending_blocks) {
			m_delegate->OnMatchFound(v.block, v.block_size);
		}
		ClearPendingBlocks();
		m_delegate->OnMatchFound(block, block_size);
	}

	void CLogReader::OnNoMatchFound() {
		ClearPendingBlocks();
	}

	bool CLogReader::AddPendingBlock(const char* block, const std::size_t block_size) {
		char* block_copy = nullptr;
		try {
			block_copy = new char[block_size];
			std::memcpy(block_copy, block, block_size);
			m_pending_blocks.push_back({block_copy, block_size});

		} catch (...) {
			delete[] block_copy;
			return false;
		}

		return true;
	}

	void CLogReader::ClearPendingBlocks() {
		for (auto v : m_pending_blocks) {
			delete[] v.block;
		}
		m_pending_blocks.clear();
	}
}