#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
};

float heuristic(Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int main() {
    const int width = 19;
    const int height = 19;

    
    vector<vector<int>> map(height, vector<int>(width, 0));
    for (int i = 3; i < 8; i++) {map[5][i] = 1;} // ściana
    for (int i = 5; i < 19; i++) {map[10][i] = 1;} // ściana
    Point start = {0, 0};
    Point goal  = {16, 18};

    // tablice pomocnicze
    vector<vector<float>> g(height, vector<float>(width, INFINITY)); // koszt dojścia
    vector<vector<Point>> parent(height, vector<Point>(width, {-1, -1}));
    vector<vector<bool>> closed(height, vector<bool>(width, false)); // odwiedzone

    g[start.y][start.x] = 0;

    // lista otwarta – najprostsza: wektor z punktami
    vector<Point> open;
    open.push_back(start);

    while (!open.empty()) {
        // znajdź punkt z najmniejszym f = g + h
        int best_i = 0;
        float best_f = g[open[0].y][open[0].x] + heuristic(open[0], goal);

        for (int i = 1; i < open.size(); i++) {
            float f = g[open[i].y][open[i].x] + heuristic(open[i], goal);
            if (f < best_f) {
                best_f = f;
                best_i = i;
            }
        }

        Point current = open[best_i];
        open.erase(open.begin() + best_i);

        if (current.x == goal.x && current.y == goal.y) {
            cout << "Cel osiagniety!\n";
            break;
        }

        closed[current.y][current.x] = true;

        
        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};

        for (int i = 0; i < 4; i++) {
            Point nb = { current.x + dx[i], current.y + dy[i] };

            if (nb.x < 0 || nb.x >= width || nb.y < 0 || nb.y >= height) continue;
            if (map[nb.y][nb.x] == 1) continue;
            if (closed[nb.y][nb.x]) continue;

            float new_g = g[current.y][current.x] + 1;

            if (new_g < g[nb.y][nb.x]) {
                g[nb.y][nb.x] = new_g;
                parent[nb.y][nb.x] = current;
                open.push_back(nb);
            }
        }
    }

    vector<Point> path;
    Point p = goal;
    while (p.x != -1 && !(p.x == start.x && p.y == start.y)) {
        path.push_back(p);
        p = parent[p.y][p.x];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());

    // wypisanie mapy
    cout << "\nMapa:\n";
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            bool onPath = false;
            for (auto pt : path)
                if (pt.x == x && pt.y == y) onPath = true;

            if (x == start.x && y == start.y) cout << "S ";
            else if (x == goal.x && y == goal.y) cout << "F ";
            else if (map[y][x] == 1) cout << "X ";
            else if (onPath) cout << "* ";
            else cout << ". ";
        }
        cout << endl;
    }
}
