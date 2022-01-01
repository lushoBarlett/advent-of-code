#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <sstream>

#include "./board.hpp"

int main() {
	freopen("./in.txt", "r", stdin);

	std::vector<uint> numbers;
	std::string string_numbers;

	std::getline(std::cin, string_numbers);

	std::stringstream ss(string_numbers);

	for (uint n; ss >> n; ss.ignore())
		numbers.push_back(n);

	std::vector<Board> boards;
	for (int n; std::cin >> n;) {
		boards.push_back(Board());
		auto &board = boards.rbegin()->board;

		board[0].number = n;

		for (size_t i = 1; i < BOARD_SIZE * BOARD_SIZE; i++)
			std::cin >> board[i].number;
	}

	for (uint number : numbers) {
		for (Board& board : boards) {
			board.mark(number);
			if (board.bingo()) {
				std::cout << board.bingo_score() * number << std::endl;
				return 0;
			}
		}
	}
}