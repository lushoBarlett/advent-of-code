#include <iostream>
#include <string>
#include <vector>

constexpr int bit_size = 12;

std::vector<int> filter_pop_count(std::vector<int>& numbers, size_t bit, bool most_common) {
	int pop_count = 0;
	for (int number : numbers)
		pop_count += (number >> bit) & 1;

	int odd_corrected = numbers.size() / 2 + numbers.size() % 2;
	
	int collect;
	if (pop_count >= odd_corrected)
		collect = most_common ? 1 : 0;
	else
		collect = most_common ? 0 : 1;

	std::vector<int> answer;
	for (int number : numbers)
		if (((number >> bit) & 1) == collect)
			answer.push_back(number);

	return answer;
}

int main() {
	freopen("./in.txt", "r", stdin);

	std::string binary;
	std::vector<int> numbers;

	while (std::cin >> binary) {
		int number = strtoul(binary.c_str(), nullptr, 2);
		numbers.push_back(number);
	}

	std::vector<int> oxigen = numbers, co2 = numbers;
	for (int bit = bit_size - 1; bit >= 0; bit--) {

		if (oxigen.size() > 1)
			oxigen = filter_pop_count(oxigen, bit, true);

		if (co2.size() > 1)
			co2 = filter_pop_count(co2, bit, false);
	}

	std::cout << oxigen[0] * co2[0] << std::endl;
}