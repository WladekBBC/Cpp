#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


vector<vector<int>> loadMapFromFile(const string& filename, int& width, int& height) {
    vector<vector<int>> map;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Nie mozna otworzyc pliku: " << filename << endl;
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

struct Point {
    int x;
    int y;
};

float h_funkcja(Point current, Point finish){
    return sqrt(pow(current.x - finish.x, 2) + pow(current.y - finish.y, 2));
}

vector<Point> aStarAlgorithm(vector<vector<int>>& map, Point start, Point finish){

    if(map.empty() || map[0].empty()){
        return {};
    }
    if(start.x < 0 || start.x >= map.size() || start.y < 0 || start.y >= map.size()){
        return {};
    }
    if(finish.x < 0 || finish.x >= map.size() || finish.y < 0 || finish.y >= map.size()){
        return {};
    }
    


    int przeszkoda = 5;
    int szerokosc = map[0].size();
    int wysokosc = map.size();

    if(map[start.y][start.x] == przeszkoda || map[finish.y][finish.x] == przeszkoda){
        return {};
    }

    vector<vector<float>> g_koszt(wysokosc, vector<float>(szerokosc, 999999999));
    vector<vector<Point>> sciezka(wysokosc, vector<Point>(szerokosc, {-1, -1}));
    vector<vector<bool>> zamknieta(wysokosc, vector<bool>(szerokosc, false));
    vector<Point> lista_otwarta;

    g_koszt[start.y][start.x] = 0;
    lista_otwarta.push_back(start);

    bool sciezka_znaleziona = false;
    while(!lista_otwarta.empty()){
        int best_i = 0;
        float best_f = h_funkcja(lista_otwarta[0], finish) + g_koszt[lista_otwarta[0].y] [lista_otwarta[0].x];
        for(int i = 1; i < lista_otwarta.size(); i++){
            float f = h_funkcja(lista_otwarta[i], finish) + g_koszt[lista_otwarta[i].y][lista_otwarta[i].x];
            if(f < best_f){
                best_f = f;
                best_i = i;
            }
        }

        Point obecny = lista_otwarta[best_i];
        lista_otwarta.erase(lista_otwarta.begin() + best_i);

        if(obecny.x == finish.x && obecny.y == finish.y){
            sciezka_znaleziona = true;
            break; 
        }

        zamknieta[obecny.y][obecny.x] = true;

        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};

        for(int i = 0; i < 4; i++){
            Point sasiad = {obecny.x + dx[i], obecny.y + dy[i]};
            if(sasiad.x < 0 || sasiad.x >= szerokosc || sasiad.y < 0 || sasiad.y >= wysokosc) continue;
            if(map[sasiad.y][sasiad.x] == przeszkoda) continue;
            if(zamknieta[sasiad.y][sasiad.x] == true) continue;

            float nowy_g = g_koszt[obecny.y][obecny.x] + 1;
            if(nowy_g < g_koszt[sasiad.y][sasiad.x]){
                g_koszt[sasiad.y][sasiad.x] = nowy_g;
                sciezka[sasiad.y][sasiad.x] = obecny;
                lista_otwarta.push_back(sasiad);
            }
        }
    }

    vector<Point> path;
    if (sciezka_znaleziona) {
        Point p = finish;
        while (p.x != -1 && !(p.x == start.x && p.y == start.y)) {
            path.push_back(p);
            p = sciezka[p.y][p.x];
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
    
    Point start = {2, 2};
    Point goal  = {19, 19};
    cout << "Szukanie sciezki\n";
    vector<Point> path = aStarAlgorithm(map, start, goal);

    if (path.empty()) {
        cout << "Nie znaleziono sciezki\n";
    } else {
        cout << "Sciezka znaleziona\n";
        cout << "\nMapa:\n";
        for (int y = height - 1; y >= 0; y--) {
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
    
    for(int i = 0; i < path.size(); i++){
        cout<< "(" <<path[i].x<< "," <<path[i].y<< ") " ;
    }
    return 0;
}