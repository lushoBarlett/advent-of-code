#include <iostream>
#include <vector>

constexpr uint DAYS = 80;

struct FishAutomaton {

	const static uint BORN_TIMER = 8;
	const static uint SPAWN_TIMER = 6;

	uint timer;

	FishAutomaton() : timer{BORN_TIMER} {}
	FishAutomaton(uint t) : timer{t} {}

	bool transition() {
		bool should_spawn = timer == 0;

		timer = should_spawn ? SPAWN_TIMER : timer - 1;

		return should_spawn;
	}
};

int main() {
	freopen("./in.txt", "r", stdin);

	std::vector<FishAutomaton> fishes;

	uint fish_timer;

	while(std::cin >> fish_timer) {
		getchar();
		fishes.push_back(FishAutomaton(fish_timer));
	}

	for (size_t i = DAYS; i--;) {
		uint spawn = 0;

		for (FishAutomaton& fish : fishes)
			spawn += fish.transition();

		for (size_t s = spawn; s--;)
			fishes.push_back(FishAutomaton());
	}

	std::cout << fishes.size() << std::endl;
}