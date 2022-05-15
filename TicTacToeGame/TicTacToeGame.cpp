// TicTacToeGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

using namespace std;

const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char NO_ONE = 'N';
const char TIE = 'T';
bool AI_FIRST = true;

void instructions();
char askYesNo(string question);
int askNumber(string question, int high, int low = 0);
char humanPiece();
char opponent(char piece);
void displayBoard(const vector<char>& board);
char winner(const vector<char>& board);
bool isLegal(int move, const vector<char>& board);
int humanMove(const vector<char>& board, char human);
int computerMove(const vector<char> board, char computer);
void announseWinner(char winner, char human, char computer);

int main()
{
    int move;
    const int NUM_SQUARES = 9;
    vector<char> board(NUM_SQUARES, EMPTY);
    char human = humanPiece();
    char computer = opponent(human);
    char turn = X;

    instructions();
    displayBoard(board);

    while (winner(board) == NO_ONE) {
        if (turn == human) {
            move = humanMove(board, human);
            board[move] = human;
        }
        else {
            move = computerMove(board, computer);
            board[move] = computer;
        }

        displayBoard(board);
        turn = opponent(turn);
    }
    announseWinner(winner(board), human, computer);
    return 0;
}

void instructions() {
    cout << "Hello and welcome to Tic-Tac-Toe Game!" << "\n";
    cout << "In this game you play vs computer using chars X or O." << "\n";
    cout << "You have a field like:" << "\n\n";
    cout << "0 | 1 | 2" << "\n";
    cout << "---------" << "\n";
    cout << "3 | 4 | 5" << "\n";
    cout << "---------" << "\n";
    cout << "6 | 7 | 8" << "\n";
    cout << "Each number in that cell is your choising number" << "\n";
    cout << "Good luck!" << "\n";
}

char askYesNo(string question) {
    char answer;

    while (true) {
        cout << question << " (y/n) ";
        cin >> answer;
        cout << "\n";

        if (answer == 'y' || answer == 'n') {
            return answer;
        }
    }
}

int askNumber(string question, int high, int low) {
    int answer;

    while (true) {
        cout << question << " (" << low << "-" << high << ") ";
        cin >> answer;
        cout << "\n";

        if (answer <= high && answer >= low)
            return answer;
    }
}

char humanPiece() {
    return askYesNo("You'd like to start the first?") == 'y' ? X : O;
}

char opponent(char piece) {
    return piece == X ? O : X;
}

void displayBoard(const vector<char>& board) {
    cout << board[0] << "|" << board[1] << "|" << board[2] << "\n";
    cout << "-----" << "\n";
    cout << board[3] << "|" << board[4] << "|" << board[5] << "\n";
    cout << "-----" << "\n";
    cout << board[6] << "|" << board[7] << "|" << board[8] << "\n";
    cout << "\n\n";
}

char winner(const vector<char>& board) {
    const int WINNER_ROWS[8][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8},
        {0, 4, 8},
        {2, 4, 6},
    };

    const int TOTAL_ROWS = 8;
    for (int row = 0; row < TOTAL_ROWS; row++) {
        if ((board[WINNER_ROWS[row][0]] != EMPTY) &&
            (board[WINNER_ROWS[row][0]] == board[WINNER_ROWS[row][1]]) &&
            (board[WINNER_ROWS[row][1]] == board[WINNER_ROWS[row][2]])) {
            return board[WINNER_ROWS[row][0]];
        }
    }

    if (count(board.begin(), board.end(), EMPTY) == 0) {
        return TIE;
    }

    return NO_ONE;
}

bool isLegal(int move, const vector<char>& board) {
    return (board[move] == EMPTY);
}

int humanMove(const vector<char>& board, char human) {
    int number;

    while (true) {
        number = askNumber("Select your cell", board.size() - 1, 0);

        if (isLegal(number, board)) {
            return number;
        }
        else {
            cout << "This cell is broke!" << "\n";
        }
    }
}

int computerMove(vector<char> board, char computer) {
    unsigned int move = 0;
    bool found = false;

    while (!found && move < board.size()) {
        if (isLegal(move, board)) {
            board[move] = computer;
            found = winner(board) == computer;
            board[move] = EMPTY;
        }

        if (!found) {
            ++move;
        }
    }

    if (!found) {
        move = 0;
        char human = opponent(computer);

        while (!found && move < board.size()) {
            if (isLegal(move, board)) {
                board[move] = human;
                found = winner(board) == human;
                board[move] = EMPTY;
            }

            if (!found) {
                ++move;
            }
        }
    }

    if (!found) {
        move = 0;
        unsigned int i = 0;
        const int BEST_MOVES[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};

        if (AI_FIRST) {
            srand(static_cast<unsigned int>(time(0)));

            move = BEST_MOVES[rand() % (board.size() - 1)];

            if (isLegal(move, board)) {
                found = true;
                AI_FIRST = false;
            }
        }

        while (!found && i < board.size()) {

            move = BEST_MOVES[i];

            if (isLegal(move, board)) {
                found = true;
            }
            ++i;
        }
    }

    cout << "I shall take square number " << move << endl;

    return move;
}

void announseWinner(char winner, char human, char computer) {
    if (winner == computer) {
        cout << computer << "'s won!" << "\n";
    } else if (winner == human) {
        cout << human << "'s won!" << "\n";
    } else {
        cout << "Friendship's won!" << "\n";
    }

    cout << "Thanks for the game!" << "\n";
}
