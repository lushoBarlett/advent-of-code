#include <iostream>

int main() {
	freopen("./in.txt", "r", stdin);
	
	int increases = 0;
	int lastMeasurement, currentMeasurement;

	std::cin >> lastMeasurement;
	while (std::cin >> currentMeasurement) {
		increases += currentMeasurement > lastMeasurement;
		lastMeasurement = currentMeasurement;
	}

	std::cout << increases << std::endl;
}