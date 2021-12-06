#include <iostream>
#include <string>

int main() {
	freopen("./in.txt", "r", stdin);

	std::string action;
	int number, position = 0, depth = 0;
	while (std::cin >> action) {
		std::cin >> number;
		if (action == "down")
			depth += number;
		else if (action == "up")
			depth -= number;
		else
			position += number;
	}

	std::cout << position * depth << std::endl;
}