#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Queen8Puzzle {
private:
    int initialNode[3][3], goalNode[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 0} };
    string data;

public:
    void generate8queenPuzzle();
    void showState();
    bool checkGoal();
    int MisplacedTiles(const int currentState[3][3]);
    bool solve8Puzzle();
};

struct PuzzleState {
    int state[3][3];
    int cost;  // Cost based on the heuristic (Misplaced Tiles)
};

struct CompareStates {
    bool operator()(const PuzzleState& a, const PuzzleState& b) {
        return a.cost > b.cost; // Priority is based on the cost
    }
};

void Queen8Puzzle::generate8queenPuzzle() {
    cout << "\n***create initial node state 0-8***\n";

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << "Insert at [" << i << "][" << j << "] : ";
            cin >> initialNode[i][j];
        }
    }
}

void Queen8Puzzle::showState() {
    cout << "\n***state***\n";

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << initialNode[i][j] << "   ";
        }
        cout << endl;
    }
}

bool Queen8Puzzle::checkGoal() {
    bool check = true;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (initialNode[i][j] != goalNode[i][j]) {
                check = false;
            }
        }
    }

    return check;
}

int Queen8Puzzle::MisplacedTiles(const int currentState[3][3]) {
    int misplacedCount = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (currentState[i][j] != goalNode[i][j]) {
                misplacedCount++;
            }
        }
    }

    return misplacedCount;
}

bool isValidMove(int x, int y) {
    return x >= 0 && x < 3 && y >= 0 && y < 3;
}

bool Queen8Puzzle::solve8Puzzle() {
    priority_queue<PuzzleState, vector<PuzzleState>, CompareStates> pq;
    vector<PuzzleState> solutionSteps;
    PuzzleState initial;
    initial.cost = MisplacedTiles(initialNode);
    copy(&initialNode[0][0], &initialNode[0][0] + 9, &initial.state[0][0]);
    pq.push(initial);

    while (!pq.empty()) {
        PuzzleState current = pq.top();
        pq.pop();

        solutionSteps.push_back(current);

        if (MisplacedTiles(current.state) == 0) {
            // Goal state is reached
            for (const PuzzleState& step : solutionSteps) {
                cout << "Step Cost: " << step.cost << endl;
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        cout << step.state[i][j] << "   ";
                    }
                    cout << endl;
                }
                cout << "--------" << endl;
            }
            return true;
        }

        int blankRow, blankCol;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (current.state[i][j] == 0) {
                    blankRow = i;
                    blankCol = j;
                }
            }
        }

        int dx[] = { -1, 1, 0, 0 };
        int dy[] = { 0, 0, -1, 1 };

        for (int i = 0; i < 4; i++) {
            int newRow = blankRow + dx[i];
            int newCol = blankCol + dy[i];

            if (isValidMove(newRow, newCol)) {
                PuzzleState nextState;
                copy(&current.state[0][0], &current.state[0][0] + 9, &nextState.state[0][0]);
                swap(nextState.state[blankRow][blankCol], nextState.state[newRow][newCol]);
                nextState.cost = MisplacedTiles(nextState.state);
                pq.push(nextState);
            }
        }
    }

    return false;
}

int main() {
    Queen8Puzzle p1;

    p1.generate8queenPuzzle();
    p1.showState();

    if (p1.solve8Puzzle()) {
        cout << "Congratulations! You reached the goal state.\n";
    }
    else {
        cout << "The goal state is not reached yet.\n";
    }

    cin.get(); // Wait for user input before closing
    return 0;
}