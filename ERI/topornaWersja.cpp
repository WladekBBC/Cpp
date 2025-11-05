#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Point {
    int x, y;
};

float heuristic(Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

vector<vector<int>> loadMapFromFile(const string& filename, int& width, int& height) {
    vector<vector<int>> map;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Blad: Nie mozna otworzyc pliku: " << filename << endl;
        width = 0; height = 0;
        return map;
    }
    string line;
    while (getline(file, line)) {
        vector<int> row;
        stringstream ss(line);
        int cell_value;
        while (ss >> cell_value) { row.push_back(cell_value); }
        if (!row.empty()) { map.push_back(row); }
    }
    
    file.close();
    if (!map.empty()) {
        height = map.size();
        width = map[0].size();
    } else {
        height = 0; width = 0;
    }
    return map;
}

vector<Point> aStar(const vector<vector<int>>& map, Point start, Point goal) {
    
    if (map.empty() || map[0].empty()) {
        return {};
    }
    
    int height = map.size();
    int width = map[0].size();

    vector<vector<float>> g(height, vector<float>(width, INFINITY));
    vector<vector<Point>> parent(height, vector<Point>(width, {-1, -1}));
    vector<vector<bool>> closed(height, vector<bool>(width, false));

    g[start.y][start.x] = 0;
    vector<Point> open;
    open.push_back(start);

    bool path_found = false;
    while (!open.empty()) {
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
            path_found = true;
            break;
        }

        closed[current.y][current.x] = true;

        //kroki lewo prawo gora dol
        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};

        for (int i = 0; i < 4; i++) {
            Point neighbour = { current.x + dx[i], current.y + dy[i] };
            if (neighbour.x < 0 || neighbour.x >= width || neighbour.y < 0 || neighbour.y >= height) continue;
            if (map[neighbour.y][neighbour.x] == 5) continue;
            if (closed[neighbour.y][neighbour.x]) continue;

            float new_g = g[current.y][current.x] + 1;
            if (new_g < g[neighbour.y][neighbour.x]) {
                g[neighbour.y][neighbour.x] = new_g;
                parent[neighbour.y][neighbour.x] = current;
                open.push_back(neighbour);
            }
        }
    }

    vector<Point> path;
    if (path_found) {
        Point p = goal;
        while (p.x != -1 && !(p.x == start.x && p.y == start.y)) {
            path.push_back(p);
            p = parent[p.y][p.x];
        }
        path.push_back(start);
        reverse(path.begin(), path.end());
    }
    
    return path; 
}


int main() {
    int width, height;
    string filename = "/Users/vladberezhnyi/Cpp/ERI/grid.txt";
    vector<vector<int>> map = loadMapFromFile(filename, width, height);

    if (width == 0 || height == 0) {
        cout << "Mapa nie zostala wczytana" << endl;
        return 1;
    }
    
    Point start = {0, 0};
    Point goal  = {19, 5};
    cout << "Szukanie sciezki...\n";
    vector<Point> path = aStar(map, start, goal);

    if (path.empty()) {
        cout << "Nie znaleziono sciezki\n";
    } else {
        cout << "Sciezka znaleziona!\n";
        cout << "\nMapa:\n";
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                bool onPath = false;
                for (auto pt : path)
                    if (pt.x == x && pt.y == y) onPath = true;

                if (x == start.x && y == start.y) cout << "S ";
                else if (x == goal.x && y == goal.y) cout << "F ";
                else if (map[y][x] == 5) cout << "X ";
                else if (onPath) cout << "* ";
                else cout << ". ";
            }
            cout << endl;
        }
    }
    
    for(int i = 0; i<path.size(); i++){
        cout<<"("<<path[i].x<<","<<path[i].y<<") ";
    }
    return 0;
}