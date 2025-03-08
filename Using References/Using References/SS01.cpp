#include <cstdlib>
#include <ctime>
#include <iostream>

void RollTwoDice(int& dice1, int& dice2);

int main() {
	srand((int)time(0));

	int dice1, dice2;

	dice1 = 0;
	dice2 = 0;

	std::cout << "The dice are currently: " << dice1 << ", " << dice2 << std::endl;

	RollTwoDice(dice1, dice2);

	std::cout << "The dice rolled: " << dice1 << ", " << dice2 << std::endl;

	return 0;
}

void RollTwoDice(int& dice1, int& dice2) {
	dice1 = (rand() % 6) + 1;
	dice2 = (rand() % 6) + 1;
}