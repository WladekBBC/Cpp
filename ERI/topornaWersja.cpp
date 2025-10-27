#include <iostream> // Do wypisywania na ekran (cout)
#include <vector>   // Do używania "dynamicznych tablic" czyli wektorów
#include <cmath>    // Do funkcji matematycznych jak pierwiastek (sqrt) i potęga (pow)
#include <algorithm>// Do funkcji reverse, która odwraca kolejność w wektorze

// Używamy standardowej przestrzeni nazw, żeby nie pisać std:: przed każdym cout, vector itp.
using namespace std;

// Prosta struktura do przechowywania współrzędnych (x, y) punktu.
// Zamiast pisać dwie zmienne int x, int y, możemy mieć jedną zmienną typu Point.
struct Point {
    int x, y;
};

// To jest nasza "magiczna" funkcja, czyli heurystyka.
// Szacuje ona koszt dotarcia z punktu 'a' do punktu 'b' w linii prostej.
// Używa twierdzenia Pitagorasa: c^2 = a^2 + b^2, więc c = sqrt(a^2 + b^2).
// To jest nasze "h" z wzoru f = g + h.
float heuristic(Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int main() {
    // --- KROK 1: PRZYGOTOWANIE MAPY I DANYCH ---

    // Definiujemy rozmiar naszej mapy/siatki.
    const int width = 19;
    const int height = 19;

    // Tworzymy mapę jako dwuwymiarowy wektor (tablica w tablicy).
    // Początkowo każde pole ma wartość 0, co oznacza "puste, można chodzić".
    vector<vector<int>> map(height, vector<int>(width, 0));

    // Rysujemy ściany na mapie. Wartość 1 oznacza "ściana, nie można chodzić".
    for (int i = 3; i < 8; i++) {map[5][i] = 1;} // pozioma ściana
    for (int i = 5; i < 19; i++) {map[10][i] = 1;} // druga pozioma ściana

    // Definiujemy punkt startowy i końcowy naszej podróży.
    Point start = {0, 0};
    Point goal  = {16, 18};

    // --- KROK 2: PRZYGOTOWANIE "NOTESÓW" ALGORYTMU ---

    // Tablica 'g' przechowuje koszt dojścia od startu do danego pola.
    // Na początku wszędzie wpisujemy "nieskończoność", bo nie znamy jeszcze żadnej drogi.
    // To jest nasze "g" z wzoru f = g + h.
    vector<vector<float>> g(height, vector<float>(width, INFINITY));

    // Tablica 'parent' pozwoli nam odtworzyć ścieżkę na końcu.
    // Dla każdego pola zapamiętamy, z którego pola do niego przyszliśmy.
    // Na początku ustawiamy "rodziców" na nieistniejący punkt {-1, -1}.
    vector<vector<Point>> parent(height, vector<Point>(width, {-1, -1}));

    // Tablica 'closed' to nasza "Lista Zamknięta".
    // Będziemy tu zaznaczać pola, które już przetworzyliśmy i nie chcemy do nich wracać.
    // Na początku wszystkie pola są "nieodwiedzone" (false).
    vector<vector<bool>> closed(height, vector<bool>(width, false));

    // Ustawiamy koszt dojścia do pola startowego na 0, bo już na nim jesteśmy.
    g[start.y][start.x] = 0;

    // To jest nasza "Lista Otwarta". Na razie zawiera tylko punkt startowy.
    // Będziemy z niej wybierać kolejne pola do sprawdzenia.
    vector<Point> open;
    open.push_back(start);

    // --- KROK 3: GŁÓWNA PĘTLA ALGORYTMU ---

    // Pętla działa, dopóki są jakieś punkty na Liście Otwartej do rozważenia.
    while (!open.empty()) {
        
        // "Toporne" szukanie najlepszego punktu na Liście Otwartej.
        // Przeglądamy całą listę 'open' i szukamy punktu z najniższym 'f' (g + h).
        int best_i = 0;
        float best_f = g[open[0].y][open[0].x] + heuristic(open[0], goal);

        for (int i = 1; i < open.size(); i++) {
            float f = g[open[i].y][open[i].x] + heuristic(open[i], goal);
            if (f < best_f) {
                best_f = f;
                best_i = i;
            }
        }

        // Wybraliśmy najlepszy punkt. Nazywamy go 'current'.
        Point current = open[best_i];
        // Usuwamy go z Listy Otwartej, bo zaraz go przetworzymy.
        open.erase(open.begin() + best_i);

        // Jeśli dotarliśmy do celu, możemy przerwać pętlę i świętować.
        if (current.x == goal.x && current.y == goal.y) {
            cout << "Cel osiagniety!\n";
            break;
        }

        // Dodajemy 'current' do Listy Zamkniętej. Już tu nie wrócimy.
        closed[current.y][current.x] = true;

        // --- KROK 4: PRZEGLĄDANIE SĄSIADÓW ---
        
        // Definiujemy ruchy: w prawo (1,0), w lewo (-1,0), w dół (0,1), w górę (0,-1).
        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};

        // Sprawdzamy każdego z czterech sąsiadów.
        for (int i = 0; i < 4; i++) {
            Point nb = { current.x + dx[i], current.y + dy[i] }; // nb = neighbor (sąsiad)

            // Poniższe warunki sprawdzają, czy sąsiad jest "legalny":
            if (nb.x < 0 || nb.x >= width || nb.y < 0 || nb.y >= height) continue; // Czy jest na mapie?
            if (map[nb.y][nb.x] == 1) continue;      // Czy to nie ściana?
            if (closed[nb.y][nb.x]) continue;       // Czy już go nie odwiedziliśmy?

            // Obliczamy koszt dojścia do tego sąsiada przez punkt 'current'.
            // Każdy krok kosztuje '1'.
            float new_g = g[current.y][current.x] + 1;

            // Sprawdzamy, czy nowo znaleziona droga do sąsiada jest lepsza niż poprzednia.
            if (new_g < g[nb.y][nb.x]) {
                g[nb.y][nb.x] = new_g;               // Aktualizujemy koszt dojścia
                parent[nb.y][nb.x] = current;        // Zapisujemy, że przyszliśmy tu z 'current'
                open.push_back(nb);                  // Dodajemy sąsiada do Listy Otwartej, żeby go później sprawdzić
            }
        }
    }

    // --- KROK 5: ODTWORZENIE ŚCIEŻKI ---

    vector<Point> path;
    Point p = goal;
    // Idziemy "od tyłu" - od celu do startu, korzystając z tablicy 'parent'.
    while (p.x != -1 && !(p.x == start.x && p.y == start.y)) {
        path.push_back(p);
        p = parent[p.y][p.x];
    }
    path.push_back(start); // Dodajemy na końcu punkt startowy
    
    // Ścieżka jest teraz odwrócona (od celu do startu), więc ją odwracamy.
    reverse(path.begin(), path.end());

    // --- KROK 6: WYPISANIE WYNIKU ---

    cout << "\nMapa:\n";
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            bool onPath = false;
            // Sprawdzamy, czy dany punkt (x,y) jest częścią znalezionej ścieżki.
            for (auto pt : path)
                if (pt.x == x && pt.y == y) onPath = true;

            // Rysujemy odpowiednie znaki na mapie.
            if (x == start.x && y == start.y) cout << "S ";
            else if (x == goal.x && y == goal.y) cout << "F ";
            else if (map[y][x] == 1) cout << "X ";
            else if (onPath) cout << "* ";
            else cout << ". ";
        }
        cout << endl;
    }
}