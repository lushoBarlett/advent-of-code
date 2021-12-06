#include <iostream>
#include <string>

int main() {
	freopen("./in.txt", "r", stdin);

	std::string action;
	int number, position = 0, depth = 0, aim = 0;
	while (std::cin >> action) {
		std::cin >> number;
		if (action == "down")
			aim += number;
		else if (action == "up")
			aim -= number;
		else {
			position += number;
			depth += number * aim;
		}
	}

	std::cout << position * depth << std::endl;
}