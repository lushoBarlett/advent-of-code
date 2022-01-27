#include <iostream>
#include <array>
#include <memory>

constexpr uint DAYS = 256;

struct BigInt {
	std::string value;

	BigInt() = default;
	BigInt(const std::string& v) {
		for (auto it = v.rbegin(); it != v.rend(); it++)
			value.push_back(*it);
	}

	struct DigitSumResult {
		char result;
		bool carry;
	};

	static DigitSumResult digit_sum(char a, char b, bool carry) {
		char number_result = a + b - '0' - '0' + carry;

		carry = number_result > 9;

		char result = carry ? number_result - 10 : number_result;

		return { char('0' + result), carry };
	}

	BigInt operator+(const BigInt& n) const {
		BigInt bigint;
		DigitSumResult sum = { '0', false };

		size_t i;

		for (i = 0; i < value.size() && i < n.value.size(); i++) {
			sum = digit_sum(value[i], n.value[i], sum.carry);
			bigint.value.push_back(sum.result);
		}
		
		const std::string& rest = value.size() > n.value.size() ? value : n.value;

		for (; i < rest.size(); i++) {
			sum = digit_sum(rest[i], '0', sum.carry);
			bigint.value.push_back(sum.result);
		}

		sum = digit_sum('0', '0', sum.carry);
		if (sum.result != '0')
			bigint.value.push_back(sum.result);

		return bigint;
	}

	BigInt& operator+=(const BigInt& n) {
		BigInt result = *this + n;

		return *this = std::move(result);
	}
};

std::ostream& operator<<(std::ostream& os, const BigInt& n) {
	if (!n.value.size())
		os << '0';

	for (auto it = n.value.rbegin(); it != n.value.rend(); it++)
		os << *it;
	
	return os;
}

struct FishGroupAutomaton {

	static const uint BORN_TIMER = 8;
	static const uint SPAWN_TIMER = 6;

	uint timer;
	BigInt amount;

	BigInt transition() {
		bool should_spawn = timer == 0;

		timer = should_spawn ? SPAWN_TIMER : timer - 1;

		return should_spawn ? amount : BigInt();
	}
};

typedef std::array<FishGroupAutomaton, FishGroupAutomaton::BORN_TIMER + 1> FishGroups;

void rotate_fish_groups(FishGroups& fish_groups, BigInt spawn) {
	auto spawn_group = fish_groups[0];

	for (size_t i = 0; i < fish_groups.size() - 1; i++)
		fish_groups[i] = fish_groups[i + 1];

	fish_groups[FishGroupAutomaton::SPAWN_TIMER].amount += spawn_group.amount;

	fish_groups[FishGroupAutomaton::BORN_TIMER] = { FishGroupAutomaton::BORN_TIMER, spawn };
}

int main() {

	freopen("./in.txt", "r", stdin);

	std::array<FishGroupAutomaton, FishGroupAutomaton::BORN_TIMER + 1> fish_groups;

	for (size_t i = 0; i < fish_groups.size(); i++)
		fish_groups[i].timer = i;

	uint fish_timer;

	while(std::cin >> fish_timer) {
		getchar();
		fish_groups[fish_timer].amount += BigInt("1");
	}

	for (size_t i = DAYS; i--;) {
		BigInt spawn;

		for (FishGroupAutomaton& group : fish_groups)
			spawn += group.transition();

		rotate_fish_groups(fish_groups, spawn);
	}

	BigInt total_fish;
	for (const auto &group : fish_groups)
		total_fish += group.amount;
	
	std::cout << total_fish << std::endl;
}
