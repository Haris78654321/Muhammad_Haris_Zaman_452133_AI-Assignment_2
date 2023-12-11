#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

// Declarations for global variables and functions
map<vector<vector<int>>, bool> visited;
map<vector<vector<int>>, vector<vector<int>>> parent;
vector<vector<int>> goal(3, vector<int>(3));

bool visit(const vector<vector<int>>& a)
{
    return visited.find(a) != visited.end();
}

int manhattan(const vector<vector<int>>& a, int moves)
{
    // Function to calculate the Manhattan distance heuristic
    int dist = moves;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (a[i][j] != 0)
            {
                for (int k = 0; k < 3; k++)
                {
                    for (int l = 0; l < 3; l++)
                    {
                        if (a[i][j] == goal[k][l])
                            dist += abs(i - k) + abs(j - l);
                    }
                }
            }
        }
    }
    return dist;
}

bool isGoal(const vector<vector<int>>& a)
{
    return a == goal;
}

bool safe(int i, int j)
{
    return i >= 0 && i <= 2 && j >= 0 && j <= 2;
}

vector<vector<vector<int>>> neighbours(const vector<vector<int>>& a)
{
    // Function to find neighboring states by swapping the empty cell
    pair<int, int> pos;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (a[i][j] == 0)
            {
                pos.first = i;
                pos.second = j;
                break;
            }
        }
    }
    vector<vector<vector<int>>> ans;
    int dx[] = { -1, +1, 0, 0 }; // Changes in x-coordinate for each move
    int dy[] = { 0, 0, -1, +1 }; // Changes in y-coordinate for each move
    for (int k = 0; k < 4; k++)
    {
        int cx = pos.first;
        int cy = pos.second;
        vector<vector<int>> n = a;
        if (safe(cx + dx[k], cy + dy[k]))
        {
            swap(n[cx + dx[k]][cy + dy[k]], n[cx][cy]);
            ans.push_back(n);
        }
    }
    return ans;
}

typedef pair<vector<vector<int>>, int> state;

struct cmp
{
    // Comparison function for the priority queue based on Manhattan distance
    bool operator()(state& a, state& b)
    {
        int am = manhattan(a.first, a.second);
        int bm = manhattan(b.first, b.second);
        return am < bm;
    }
};

void print_path(const vector<vector<int>>& s)
{
    // Function to print the path from the initial state to the goal state
    if (parent.count(s))
        print_path(parent[s]);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", s[i][j]);
        }
        cout << endl;
    }
    cout << endl;
}

void print(const vector<vector<int>>& s)
{
    // Function to print a state
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", s[i][j]);
        }
        cout << endl;
    }
}

void solve(const vector<vector<int>>& a, int moves)
{
    // Function to solve the puzzle using A* search algorithm
    priority_queue<state, vector<state>, cmp> Q;
    Q.push(state(a, moves));
    while (!Q.empty())
    {
        vector<vector<int>> s = Q.top().first;
        Q.pop();

        visited[s] = true;

        if (isGoal(s))
        {
            print_path(s);
            break;
        }
        vector<vector<vector<int>>> ns = neighbours(s);
        vector<vector<vector<int>>>::iterator it;
        for (it = ns.begin(); it != ns.end(); it++)
        {
            vector<vector<int>> temp = *it;
            if (!visit(temp))
            {
                parent.insert(pair<vector<vector<int>>, vector<vector<int>>>(temp, s));
                Q.push(state(temp, moves + 1));
            }
        }
    }
    return;
}

int main()
{
    // Main function to take input, set goal state, and call solve function
    vector<vector<int>> a(3, vector<int>(3));

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cin >> a[i][j];
        }
    }
    cout << "Solution...\n\n";
    goal[0][0] = 1;
    goal[0][1] = 2;
    goal[0][2] = 3;
    goal[1][0] = 4;
    goal[1][1] = 5;
    goal[1][2] = 6;
    goal[2][0] = 7;
    goal[2][1] = 8;
    goal[2][2] = 0;

    solve(a, 0);
}