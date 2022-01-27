#include <iostream>
#include <set>
#include <algorithm>
#include <climits>

uint fuel_consumption(std::multiset<int>& crabs, int target) {
	uint total_fuel = 0;
	for (int crab : crabs)
		total_fuel += abs(target - crab);
	return total_fuel;	
}

int main() {
	freopen("./in.txt", "r", stdin);

	std::multiset<int> crabs;

	uint crab_horizontal_position;

	while(std::cin >> crab_horizontal_position) {
		getchar();
		crabs.insert(crab_horizontal_position);
	}

	int min_crab = *std::min_element(crabs.begin(), crabs.end());
	int max_crab = *std::max_element(crabs.begin(), crabs.end());

	uint min_fuel = UINT_MAX;
	for (int crab : crabs)
		min_fuel = std::min(min_fuel, fuel_consumption(crabs, crab));

	std::cout << min_fuel << std::endl;	
}