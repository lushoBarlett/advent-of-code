#include <iostream>
#include <array>
#include <initializer_list>

template <typename T, std::size_t size>
struct sliding_window {

private:
	std::array<T, size> container;
	size_t index = 0;

public:
	sliding_window() = default;
	sliding_window(std::array<T, size> array) : container{array} {};
	sliding_window(std::initializer_list<T> list) : container{list} {};

	void shift(const T& value) {
		container[index++] = value;
		if (index >= size)
			index = 0;
	}

	void unshift(const T& value) {
		container[index--] = value;
		if (index < 0)
			index = size - 1;
	}

	T operator[](size_t index) const {
		return container[index];
	}
};


int main() {
	freopen("./in.txt", "r", stdin);
	
	sliding_window<int, 3> window;
	int currentMeasurement;

	std::cin >> currentMeasurement;
	window.shift(currentMeasurement);
	std::cin >> currentMeasurement;
	window.shift(currentMeasurement);
	std::cin >> currentMeasurement;
	window.shift(currentMeasurement);

	const auto sum = [&window]() {
		return window[0] + window[1] + window[2];
	};

	int increases = 0;
	int lastSum = sum();

	while (std::cin >> currentMeasurement) {
		window.shift(currentMeasurement);
		increases += sum() > lastSum;
		lastSum = sum();
	}

	std::cout << increases << std::endl;
}