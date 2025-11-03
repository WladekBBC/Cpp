import numpy as np
import math
import time 

# 1 - przeszkoda
# 0 - wolne pole
# * - odwiedzane pole
mapa = np.zeros((17,17), dtype=int)

start = (0,0)
finish = (16,16)
przeszkody = []
for r in range(mapa.shape[0]):
    for c in range(mapa.shape[1]):
        if mapa[r,c] == 1:
            przeszkody.append((r,c))

def h_funkcja(x_cel, y_cel, x_n, y_n):
    return math.sqrt((x_n - x_cel)**2 + (y_n - y_cel)**2)

def g_funkcja(g_current):
    return g_current + 1  

def f_funkcja(g,h):
    return g + h


open_list = [start]
closed_list = []

# fg_dict przechowuje g, h, f i rodzica (do odtworzenia ścieżki)
fg_dict = {start: {'g':0, 'h':h_funkcja(*finish, *start), 'f':h_funkcja(*finish, *start), 'parent': None}}

# możliwe ruchy: góra, dół, lewo, prawo
moves = [(-1,0),(1,0),(0,-1),(0,1)]

while open_list:
    # --- POCZĄTEK BLOKU WIZUALIZACJI W KAŻDYM KROKU ---
    mapa_path = np.copy(mapa).astype(str)
    # Zastąp '0' kropkami dla lepszej czytelności
    mapa_path[mapa_path == '0'] = '.'

    # Oznacz wszystkie odwiedzone węzły (closed_list)
    for node in closed_list:
        mapa_path[node[0], node[1]] = '*'
        
    # Oznacz wszystkie węzły na liście otwartej (open_list)
    for node in open_list:
        mapa_path[node[0], node[1]] = '#'

    # Wybierz najlepszy węzeł, ale jeszcze go nie usuwaj z open_list
    current = min(open_list, key=lambda x: fg_dict[x]['f'])
    
    # Oznacz aktualnie przetwarzany węzeł
    mapa_path[current[0], current[1]] = '@'
    mapa_path[start[0], start[1]] = 'S'
    mapa_path[finish[0], finish[1]] = 'F'
    
    # Wydrukuj mapę w obecnym stanie
    print("\n---------------------------------")
    print(f"Aktualny węzeł: {current}, f = {fg_dict[current]['f']:.2f}")
    print("Mapa stanu:")
    print(mapa_path)
    time.sleep(0.05) # Pauza, aby można było zaobserwować zmiany
    

    if current == finish:
        print("\nCel osiągnięty!")
        path = []
        while current:
            path.append(current)
            current = fg_dict[current]['parent']
        path.reverse()
        print("Odnaleziona ścieżka:", path)
        
        # Wizualizacja ostatecznej ścieżki
        final_map = np.copy(mapa).astype(str)
        final_map[final_map == '0'] = '.'
        for r, c in path:
            if (r,c) != start and (r,c) != finish:
                final_map[r,c] = '+' # Użyj '+' do oznaczenia ścieżki
        final_map[start[0], start[1]] = 'S' # Start
        final_map[finish[0], finish[1]] = 'F' # Finish
        print("\nMapa z ostateczną ścieżką:")
        print(final_map)
        
        break

    open_list.remove(current)
    closed_list.append(current)

    for move in moves:
        neighbor = (current[0]+move[0], current[1]+move[1])
        
        if not (0 <= neighbor[0] < mapa.shape[0] and 0 <= neighbor[1] < mapa.shape[1]):
            continue

        if neighbor in przeszkody or neighbor in closed_list:
            continue
        
        g = g_funkcja(fg_dict[current]['g'])
        h = h_funkcja(*finish, *neighbor)
        f = f_funkcja(g,h)

        if neighbor not in open_list or g < fg_dict[neighbor]['g']:
            fg_dict[neighbor] = {'g': g, 'h': h, 'f': f, 'parent': current}
            if neighbor not in open_list:
                open_list.append(neighbor)
        
else: 
    print("Nie znaleziono ścieżki do celu.")