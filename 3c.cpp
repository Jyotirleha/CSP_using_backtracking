#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<vector<int>> graph;
vector<int> color;
vector<char> colors;

// Check whether a color can be assigned to a state
bool isSafe(int state, int c)
{
    for (int i = 0; i < n; i++)
    {
        if (graph[state][i] && color[i] == c)
            return false;
    }

    return true;
}

// DFS based Backtracking
bool solve(int state)
{
    // All states are colored
    if (state == n)
        return true;

    // Try every available color
    for (int c = 0; c < m; c++)
    {
        if (isSafe(state, c))
        {
            color[state] = c;

            // Move to next state
            if (solve(state + 1))
                return true;

            // Backtrack
            color[state] = -1;
        }
    }

    return false;
}

int main()
{
    cout << "Enter the number of states: ";
    cin >> n;

    cout << "Enter the number of colors: ";
    cin >> m;

    colors.resize(m);

    cout << "Enter the colors: ";
    for (int i = 0; i < m; i++)
        cin >> colors[i];

    graph.assign(n, vector<int>(n, 0));
    color.assign(n, -1);

    cout << "Enter the connections (-1 for end):\n";

    int u, v;

    while (true)
    {
        cin >> u;

        if (u == -1)
            break;

        cin >> v;

        // Convert state numbers to array indices
        u--;
        v--;

        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    if (solve(0))
    {
        cout << "\nOutput:\n";

        for (int i = 0; i < n; i++)
        {
            cout << i + 1 << " - " << colors[color[i]] << endl;
        }
    }
    else
    {
        cout << "\nNo valid coloring is possible.\n";
    }

    return 0;
}