#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>
#include <thread>   
#include <chrono>   

using namespace std;


struct Point {
    int x, y;
    bool operator==(const Point& other) const { return x == other.x && y == other.y; }
};

struct Node {
    int x, y;
    float g, h, f; 
    int parent_x, parent_y;
    Node(int x = 0, int y = 0) : x(x), y(y), g(0), h(0), f(0), parent_x(-1), parent_y(-1) {}
};

struct CompareNode {
    bool operator()(const Node& a, const Node& b) const { return a.f > b.f; }
};


float heuristic(Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

vector<Point> reconstructPath(Point end, const vector<vector<Node>>& all_nodes) {
    vector<Point> path;
    Point current = end;
    while (current.x != -1) {
        path.push_back(current);
        const Node& node = all_nodes[current.y][current.x];
        current = {node.parent_x, node.parent_y};
    }
    reverse(path.begin(), path.end());
    return path;
}


void printMapState(
    const vector<vector<int>>& map, 
    const vector<vector<bool>>& closed_list,
    const vector<vector<Node>>& all_nodes,
    const priority_queue<Node, vector<Node>, CompareNode>& open_list_pq,
    Point current, Point start, Point end) 
{

    priority_queue<Node, vector<Node>, CompareNode> temp_pq = open_list_pq;
    vector<Point> open_points;
    while(!temp_pq.empty()) {
        open_points.push_back({temp_pq.top().x, temp_pq.top().y});
        temp_pq.pop();
    }
    
    int height = map.size();
    int width = map[0].size();
    vector<vector<char>> display_map(height, vector<char>(width));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (map[y][x] == 1) {
                display_map[y][x] = 'X'; // Przeszkoda
            } else {
                display_map[y][x] = '.'; // Wolne pole
            }
            if (closed_list[y][x]) {
                display_map[y][x] = '*'; // Odwiedzone pole
            }
        }
    }

    for (const auto& p : open_points) {
        display_map[p.y][p.x] = '#'; 
    }

    display_map[current.y][current.x] = '@'; 
    display_map[start.y][start.x] = 'S';
    display_map[end.y][end.x] = 'F';
    
    cout << "\n---------------------------------" << endl;
    cout << "Aktualny wezel: (" << current.x << ", " << current.y 
         << "), f = " << all_nodes[current.y][current.x].f << endl;
    cout << "Mapa stanu:" << endl;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            cout << display_map[y][x] << " ";
        }
        cout << endl;
    }
}


void findPathWithVisualization(const vector<vector<int>>& map, Point start, Point end) {
    int height = map.size();
    int width = map[0].size();

    priority_queue<Node, vector<Node>, CompareNode> open_list;
    vector<vector<bool>> closed_list(height, vector<bool>(width, false));
    vector<vector<Node>> all_nodes(height, vector<Node>(width));

    Node start_node(start.x, start.y);
    start_node.g = 0;
    start_node.h = heuristic(start, end);
    start_node.f = start_node.g + start_node.h;
    
    open_list.push(start_node);
    all_nodes[start.y][start.x] = start_node;

    while (!open_list.empty()) {
        Node current_node = open_list.top();
        open_list.pop();

        
        printMapState(map, closed_list, all_nodes, open_list, {current_node.x, current_node.y}, start, end);
        this_thread::sleep_for(chrono::milliseconds(50));
        

        if (closed_list[current_node.y][current_node.x]) continue;
        closed_list[current_node.y][current_node.x] = true;

        if (Point{current_node.x, current_node.y} == end) {
            vector<Point> path = reconstructPath(end, all_nodes);
            cout << "Odnaleziona sciezka:" << endl;
            for (auto& p : path)
                cout << "(" << p.x << ", " << p.y << ") ";
            cout << endl;
            return;
        }

        int dx[] = {-1, 1, 0, 0}; 
        int dy[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; ++i) {
            Point neighbor_point = {current_node.x + dx[i], current_node.y + dy[i]};

            if (neighbor_point.x < 0 || neighbor_point.x >= width || neighbor_point.y < 0 || neighbor_point.y >= height) continue;
            if (map[neighbor_point.y][neighbor_point.x] == 1 || closed_list[neighbor_point.y][neighbor_point.x]) continue;

            float g = current_node.g + 1.0f; // Koszt ruchu to 1
            float h = heuristic(neighbor_point, end);
            float f = g + h;
            
            Node& neighbor_node_ref = all_nodes[neighbor_point.y][neighbor_point.x];
            
            if (neighbor_node_ref.parent_x == -1 || g < neighbor_node_ref.g) {
                neighbor_node_ref.x = neighbor_point.x;
                neighbor_node_ref.y = neighbor_point.y;
                neighbor_node_ref.parent_x = current_node.x;
                neighbor_node_ref.parent_y = current_node.y;
                neighbor_node_ref.g = g;
                neighbor_node_ref.h = h;
                neighbor_node_ref.f = f;
                open_list.push(neighbor_node_ref);
            }
        }
    }

    cout << "Nie znaleziono sciezki do celu." << endl;
}

int main() {
    vector<vector<int>> map(17, vector<int>(17, 0));
    
    Point start = {0, 0};
    Point end = {16, 16};
    
    findPathWithVisualization(map, start, end);

    return 0;
}