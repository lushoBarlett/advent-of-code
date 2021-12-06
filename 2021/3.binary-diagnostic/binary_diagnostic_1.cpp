#include <iostream>
#include <string>
#include <array>

constexpr int bit_size = 12;

int main() {
	freopen("./in.txt", "r", stdin);

	std::string binary;
	std::array<int, bit_size> pop_count = {0};
	int numbers = 0;

	while (std::cin >> binary) {
		int number = strtoul(binary.c_str(), nullptr, 2);
		
		for (size_t i = 0, bit = 0b1; i < bit_size; i++, bit <<= 1)
			pop_count[i] += (bool)(number & bit);

		numbers++;
	}

	int gamma = 0;
	for (size_t i = 0, bit = 0; i < bit_size; i++, bit++)
		gamma |= ((numbers / 2) < pop_count[i]) << bit;

	std::cout << gamma * ((1 << bit_size) - 1 - gamma) << std::endl;
}