#include <iostream>
#include <cstdlib>
#include <ctime>

void printDoors(char& symbol1, char& symbol2, char& symbol3);
void selectPrizeDoor(int& doorPrizeNumber);
void hideBadDoor(int& doorPrizeNumber, int& selected, char& symbol1, char& symbol2, char& symbol3, int& hiddenDoor);
int getLastDoor(int& selected, int& hiddenDoor);
void swapDoors(int& selected, int& otherDoor, char& ans);
void getWinner(char& symbol1, char& symbol2, char& symbol3, int& doorPrizeNumber);
void printWinner(int& selected, int& doorPrizeNumber);


int main() {
	srand((int)time(0));

	char symbol1 = '1';
	char symbol2 = '2';
	char symbol3 = '3';

	int doorPrizeNumber = 0;

	int hiddenDoor = 0;

	selectPrizeDoor(doorPrizeNumber);

	std::cout << "The Monty Hall Game Show!" << std::endl;
	std::cout << "------------------------\n\n" << std::endl;

	printDoors(symbol1, symbol2, symbol3);

	std::cout << "Which door does the player choose (1/2/3)? " << std::endl;

	int selected = 0;
	std::cin >> selected;

	hideBadDoor(doorPrizeNumber, selected, symbol1, symbol2, symbol3, hiddenDoor);

	printDoors(symbol1, symbol2, symbol3);

	int otherDoor = getLastDoor(selected, hiddenDoor);

	std::cout << "Does the player want to switch from door " << selected << " to door " << otherDoor << " (y/n)? " << std::endl;

	char ans = 0;
	std::cin >> ans;

	swapDoors(selected, otherDoor, ans);
	std::cout << "Its time to reveal the prizes!\n\n" << std::endl;

	getWinner(symbol1, symbol2, symbol3, doorPrizeNumber);
	printDoors(symbol1, symbol2, symbol3);
	printWinner(selected, doorPrizeNumber);

	return 0;
}

void printDoors(char& symbol1, char& symbol2, char& symbol3) {
	std::cout << "   Door1    Door2    Door3" << std::endl;
	std::cout << "   +---+    +---+    +---+" << std::endl;
	std::cout << "  |     |  |     |  |     |" << std::endl;
	std::cout << "  |  " << symbol1 << "  |  |  " << symbol2 << "  |  |  " << symbol3 << "  |" << std::endl;
	std::cout << "  |     |  |     |  |     |" << std::endl;
	std::cout << "   +---+    +---+    +---+\n\n" << std::endl;
}

void selectPrizeDoor(int& doorPrizeNumber) {
	int doorSelected = (rand() % 3) + 1;

	switch (doorSelected) {
	case 1:
		doorPrizeNumber = 1;
		break;

	case 2:
		doorPrizeNumber = 2;
		break;

	case 3:
		doorPrizeNumber = 3;
		break;

	default:
		doorPrizeNumber = 1;
		break;
	}
}

void hideBadDoor(int& doorPrizeNumber, int& selected, char& symbol1, char& symbol2, char& symbol3, int& hiddenDoor) {
	hiddenDoor = (rand() % 2) + 1;
	
	if (selected == doorPrizeNumber) {
		switch (doorPrizeNumber) {
		case 1:
			if (hiddenDoor == 1) {
				symbol2 = 'x';
				hiddenDoor = 2;
			}
			else {
				symbol3 = 'x';
				hiddenDoor = 3;
			}
			break;

		case 2:
			if (hiddenDoor == 1) {
				symbol1 = 'x';
				hiddenDoor = 1;
			}
			else {
				symbol3 = 'x';
				hiddenDoor = 3;
			}
			break;

		case 3:
			if (hiddenDoor == 1) {
				symbol1 = 'x';
				hiddenDoor = 1;
			}
			else {
				symbol2 = 'x';
				hiddenDoor = 2;
			}
			break;

		default:
			if (hiddenDoor == 1) {
				symbol2 = 'x';
				hiddenDoor = 2;
			}
			else {
				symbol3 = 'x';
				hiddenDoor = 3;
			}
			break;
		}
	}
	else {
		switch (doorPrizeNumber) {
		case 1:
			if (selected == 2) {
				symbol3 = 'x';
				hiddenDoor = 3;
			}
			else {
				symbol2 = 'x';
				hiddenDoor = 2;
			}
			break;

		case 2:
			if (selected == 1) {
				symbol3 = 'x';
				hiddenDoor = 3;
			}
			else {
				symbol1 = 'x';
				hiddenDoor = 1;
			}
			break;

		case 3:
			if (selected == 1) {
				symbol2 = 'x';
				hiddenDoor = 2;
			}
			else {
				symbol1 = 'x';
				hiddenDoor = 1;
			}
			break;
		}
	}

	std::cout << hiddenDoor << std::endl;
}

int getLastDoor(int& selected, int& hiddenDoor) {
	if (selected == 1) {
		if (hiddenDoor == 2) {
			return 3;
		}
		else {
			return 2;
		}
	}
	else if (selected == 2) {
		if (hiddenDoor == 1) {
			return 3;
		}
		else {
			return 1;
		}
	}
	else {
		if (hiddenDoor == 1) {
			return 2;
		}
		else {
			return 1;
		}
	}
}

void swapDoors(int& selected, int& otherDoor, char& ans) {
	int temp = 0;

	switch (ans) {
	case 'y':
		temp = selected;
		selected = otherDoor;
		otherDoor = temp;
		std::cout << "Player swaps to door " << otherDoor << "..." << std::endl;
		break;

	case 'n':
		std::cout << "Player chooses to stay with door " << selected << "..." << std::endl;
		break;

	case 'Y':
		temp = selected;
		selected = otherDoor;
		otherDoor = temp;
		std::cout << "Player swaps to door " << otherDoor << "..." << std::endl;
		break;

	case 'N':
		std::cout << "Player chooses to stay with door " << selected << "..." << std::endl;
		break;
	}
}

void getWinner(char& symbol1, char& symbol2, char& symbol3, int& doorPrizeNumber) {
	switch (doorPrizeNumber) {
	case 1:
		symbol1 = '$';
		symbol2 = 'x';
		symbol3 = 'x';
		break;

	case 2:
		symbol1 = 'x';
		symbol2 = '$';
		symbol3 = 'x';
		break;

	case 3:
		symbol1 = 'x';
		symbol2 = 'x';
		symbol3 = '$';
		break;

	}
}

void printWinner(int& selected, int& doorPrizeNumber){
	if (selected == doorPrizeNumber) {
		std::cout << "Congratulations! The player wins!";
	}
	else {
		std::cout << "Oh no! The player loses!";
	}
}