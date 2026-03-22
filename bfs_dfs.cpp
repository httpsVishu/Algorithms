#include <iostream>
#include <queue>
#include <stack>
using namespace std;

void BFS(int edge[][50], int v, int start) {

    bool visited[50] = {false};
    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "\nBFS Traversal: ";

    while (!q.empty()) {

        int node = q.front();
        q.pop();

        cout << "v" << node + 1 << " ";

        for (int i = 0; i < v; i++) {
            if (edge[node][i] > 0 && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
}

void DFS(int edge[][50], int v, int start) {

    bool visited[50] = {false};
    stack<int> s;

    s.push(start);

    cout << "\nDFS Traversal: ";

    while (!s.empty()) {

        int node = s.top();
        s.pop();

        if (!visited[node]) {

            visited[node] = true;
            cout << "v" << node + 1 << " ";

            for (int i = v - 1; i >= 0; i--) {
                if (edge[node][i] > 0 && !visited[i]) {
                    s.push(i);
                }
            }
        }
    }
}

void createGraph(int edge[][50], int &v) {

    int e;
    char type;

    cout << "Enter number of vertices: ";
    cin >> v;

    cout << "Undirected or Directed graph? (u/d): ";
    cin >> type;

    for (int i = 0; i < v; i++)
        for (int j = 0; j < v; j++)
            edge[i][j] = 0;

    if (type == 'u') {

        for (int i = 0; i < v; i++) {
            for (int j = i; j < v; j++) {

                cout << "How many edges between v" << i + 1 << " and v" << j + 1 << ": ";
                cin >> e;

                edge[i][j] = e;
                edge[j][i] = e;
            }
        }
    }

    else if (type == 'd') {

        for (int i = 1; i <= v; i++) {
            for (int j = 1; j <= v; j++) {

                cout << "How many directed edges from v" << i << " to v" << j << ": ";
                cin >> e;

                edge[i - 1][j - 1] = e;
            }
        }
    }

    else {
        cout << "Wrong Input!";
        return;
    }

    cout << "\nAdjacency Matrix:\n";

    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            cout << edge[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {

    int edge[50][50];
    int v;

    createGraph(edge, v);

    int start;
    cout << "\nEnter starting vertex (1-" << v << "): ";
    cin >> start;

    BFS(edge, v, start - 1);
    DFS(edge, v, start - 1);

    return 0;
}