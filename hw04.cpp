// Grant Norton
// CS301
// HW04
// Due 7/3/2019
#include<iostream>
#include<iomanip>
#include<ctime>
#include<string>
using namespace std;

class Board {
	private:
		struct Space {
			string name;
			int points;
			Space* next;
			Space* prev;
		};
		Space* start;
		Space* player1;
		Space* player2;
    public:
		Board();
		~Board();
		string getSpaceName(int player);
		int getSpacePoints(int player);
		void addSpace(string name, int points);
		void move(char direction, int playerNumber, int roll);
		void reset();
		void printBoard();
};

Board::Board() {
	start = nullptr;
	player1 = nullptr;
	player2 = nullptr;
}

Board::~Board() {
	Space* p = start->next;
	Space* n = nullptr;

	if (p == start)
		delete p;
	do
	{
		n = p;
		p = p->next;
		delete n;

	} while (p != start);
	delete p;
}

string Board::getSpaceName(int player) {
	if (player == 1)
		return(player1->name);
	else
		return(player2->name);
}

int Board::getSpacePoints(int player) {
	if (player == 1)
		return(player1->points);
	else
		return(player2->points);
}

void Board::addSpace(string name, int points) {
	Space* p = new Space;
	p->name = name;
	p->points = points;
	if (start == nullptr) {
		start = p;
		p->next = p;
		p->prev = p;
		reset();
	}
	else {
		start->prev->next = p;
		p->next = start;
		p->prev = start->prev;
		start->prev = p;
	}


}

void Board::move(char direction, int playerNumber, int roll) {
	string player;
	if (direction == 'f') {
		if (playerNumber == 1) {
			for (int i = 0; i < roll; i++) {
				player1 = player1->next;
			}
		}
		else {
			for (int i = 0; i < roll; i++) {
				player2 = player2->next;
			}
		}

	}
	else if(direction == 'b'){
		if (playerNumber == 1) {
			for (int i = 0; i < roll; i++) {
				player1 = player1->prev;
			}
		}
		else {
			for (int i = 0; i < roll; i++) {
				player2 = player2->prev;
			}
		}
	}
}

void Board::reset() {
	player1 = start;
	player2 = start;
}

void Board::printBoard() {
	Space* p = start;
	cout << endl;
	cout << left << setw(20) << "SPACE" << right << setw(5) << "POINTS" << right << setw(10) << "PLAYER" << endl;
	do
	{
		cout << left << setw(20) << p->name << right << setw(6) << p->points;
		if (player1 == p) {
			cout << right << setw(11) << "player1";
		}
		if (player2 == p) {
			cout << right << setw(11) << "player2";
		}
		cout << endl;
		p = p->next;
	} while (p != start);
	cout << endl;
}




int main() {
	Board game;

	game.addSpace("Start", 0);
	game.addSpace("Winterfell", 20);
	game.addSpace("King's Landing", -15);
	game.addSpace("The Iron Islands", 5);
	game.addSpace("The Wall", 5);
	game.addSpace("Casterly Rock", -8);
	game.addSpace("Dragonstone", 10);
	game.addSpace("Dorne", 2);
	game.addSpace("Storm's End", -5);
	game.addSpace("Castle Black", 15);
	game.addSpace("Valyria", -10);
	game.addSpace("The Vale of Arryn", -5);


	srand(time(0));
	int r; 							//random number
	int player = 0;
	int scoreP1 = 50;
	int scoreP2 = 50;
	char choice;

	do
	{
		cout << "Turn # " << player + 1 << endl;
		cout << "Player " << (player % 2) + 1 << "'s turn." << endl;
		cout << "Score --> [" << scoreP1 << ":" << scoreP2 << "]" << endl;
		cout << "Player1 Space: " << game.getSpaceName(1) << endl;
		cout << "Player2 Space: " << game.getSpaceName(2) << endl;
		cout << "(F)orward,  (B)ackward,  (P)rint Board, or (Q)uit: ";
		cin >> choice;
		choice = tolower(choice);

		if (choice == 'f') {
			r = (rand() % 3) + 1;
			int playerNum = (player % 2) + 1;
			game.move('f', playerNum, r);
			cout << "---------------------------------------------------" << endl;
			cout << "You rolled a " << r << "." << endl;
			cout << "You landed on: " << game.getSpaceName(playerNum) << " for " << game.getSpacePoints(playerNum) << " points!" << endl;
			cout << "---------------------------------------------------" << endl;

			if (playerNum <= 1)
				scoreP1 += game.getSpacePoints(playerNum);
			else
				scoreP2 += game.getSpacePoints(playerNum);

			player++;

		}
		else if (choice == 'b') {
			r = (rand() % 3) + 1;
			int playerNum = (player % 2) + 1;
			game.move('b', playerNum, r);
			cout << "---------------------------------------------------" << endl;
			cout << "You rolled a " << r << "." << endl;
			cout << "You landed on: " << game.getSpaceName(playerNum) << " for " << game.getSpacePoints(player) << " points!" << endl;
			cout << "---------------------------------------------------" << endl;
			if (playerNum <= 1)
				scoreP1 += game.getSpacePoints(playerNum);
			else
				scoreP2 += game.getSpacePoints(playerNum);
			player ++;
		}
		else if (choice == 'p') {
			game.printBoard();
		}

	} while (choice != 'q' && (scoreP1 < 200 && scoreP2 < 200) && (scoreP1 > 0 && scoreP2 > 0));
	cout << endl;

	cout << "***GAME OVER***" << endl;
	cout << "Final Score:" << endl;
	cout << "Player 1: " << scoreP1 << endl;
	cout << "Player 2: " << scoreP2 << endl;
	cout << "Total Turns: " << player << endl;

	cout << endl;
	system("pause");
	return 0;
}
