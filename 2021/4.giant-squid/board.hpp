#pragma once

#include <array>

constexpr unsigned int BOARD_SIZE = 5;

struct Board {
	struct Cell {
		unsigned int number;
		bool marked = false;
	};

	std::array<Cell, BOARD_SIZE * BOARD_SIZE> board;

	Board() = default;

	void mark(unsigned int number) {
		for (Cell& cell : board)
			if (cell.number == number)
				cell.marked = true;
	}

	bool bingo() const {
		for (size_t i = 0; i < BOARD_SIZE; i++) {
			bool full = true;
			for (size_t j = 0; j < BOARD_SIZE; j++)
				full &= board[i * BOARD_SIZE + j].marked;
			
			if (full)
				return full;
		}
		
		for (size_t i = 0; i < BOARD_SIZE; i++) {
			bool full = true;
			for (size_t j = 0; j < BOARD_SIZE; j++)
				full &= board[j * BOARD_SIZE + i].marked;
			
			if (full)
				return full;
		}

		return false;
	}

	unsigned int bingo_score() const {
		unsigned int total = 0;
		for (const Cell& cell : board)
			total += !cell.marked * cell.number;
		return total;
	}
};
