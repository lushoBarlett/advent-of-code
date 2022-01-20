#include <iostream>
#include <vector>

constexpr int BOARD_SIZE = 1000;

int board[BOARD_SIZE][BOARD_SIZE];

struct HydroVent {
	int beginx;
	int beginy;
	int endx;
	int endy;
};

void place_hidrovent(HydroVent hidrovent) {
	if (hidrovent.beginx == hidrovent.endx) {
		const int direction = hidrovent.endy - hidrovent.beginy;
		
		const int unit = direction / abs(direction);

		for (size_t y = hidrovent.beginy; y != hidrovent.endy + unit; y += unit)
			board[hidrovent.beginx][y]++;
	} else if (hidrovent.beginy == hidrovent.endy) {
		const int direction = hidrovent.endx - hidrovent.beginx;
		
		const int unit = direction / abs(direction);

		for (size_t x = hidrovent.beginx; x != hidrovent.endx + unit; x += unit)
			board[x][hidrovent.beginy]++;
	} else {
		const int directionx = hidrovent.endx - hidrovent.beginx;
		const int directiony = hidrovent.endy - hidrovent.beginy;
		
		const int unitx = directionx / abs(directionx);
		const int unity = directiony / abs(directiony);

		for (size_t x = hidrovent.beginx, y = hidrovent.beginy; x != hidrovent.endx + unitx && y != hidrovent.endy + unity; x += unitx, y += unity)
			board[x][y]++;
	}
}

int main() {
	freopen("./in.txt", "r", stdin);

	std::vector<HydroVent> hidrovents;

	while (!feof(stdin)) {
		HydroVent hidrovent;
		
		scanf("%d,%d -> %d,%d", &hidrovent.beginx, &hidrovent.beginy, &hidrovent.endx, &hidrovent.endy);

		hidrovents.push_back(hidrovent);
	}
	
	for (auto hidrovent : hidrovents)
		place_hidrovent(hidrovent);
	
	int dangerous = 0;

	for (size_t i = 0; i < BOARD_SIZE; i++)
		for (size_t j = 0; j < BOARD_SIZE; j++)
			dangerous += board[i][j] > 1;
	
	std::cout << dangerous << std::endl;
}
