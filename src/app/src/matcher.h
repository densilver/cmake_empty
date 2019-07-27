#ifndef PET_CONSOLE_MATCHER_H
#define PET_CONSOLE_MATCHER_H

#include <cstddef>
#include <vector>

namespace Matcher {
	class CLogReader {
	public:
		struct Delegate {
			virtual void OnMatchFound(const char* block, const std::size_t block_size) = 0;
		};

		CLogReader();
		~CLogReader();
		bool SetFilter(const char *filter);
		bool AddSourceBlock(const char* block, const std::size_t block_size);

		void SetDelegate(Delegate* delegate);
	private:
		using MatchStatus = enum {
			HasMatch,
			HasNoMatch,
			Pending
		};
		struct MatchBlock {
			const char* block;
			std::size_t block_size;
		};

		CLogReader(const CLogReader&) = delete;
		CLogReader& operator =(const CLogReader&) = delete;

		MatchStatus Match(const char* block, std::size_t block_size, std::size_t& processed_size);
		MatchStatus MatchStar(const char* block, std::size_t block_size, std::size_t& processed_size);
		std::size_t FindEndOfLine(const char* block, const std::size_t block_size);

		void OnMatchFound(const char* block, const std::size_t block_size);
		void OnNoMatchFound();

		bool AddPendingBlock(const char* block, const std::size_t block_size);
		void ClearPendingBlocks();

		const char* m_filter;
		const char* m_cur_filter;

		std::vector<MatchBlock> m_pending_blocks;

		Delegate* m_delegate;
	};
}

#endif //PET_CONSOLE_MATCHER_H
