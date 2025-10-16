import numpy as np

# 3 - start
# 5 - cel
# 1 - przeszkoda
# 0 - wolne pole
# * - odwiedzane pole
mapa = np.array([
    [0, 0, 0, 0, 0],
    [0, 1, 0, 0, 0],
    [0, 0, 1, 0, 0],
    [0, 0, 0, 1, 0], 
    [0, 0, 0, 0, 1]
])

start = (3,2)
finish = (3,4)
przeszkody = []
for r in range(mapa.shape[0]):
    for c in range(mapa.shape[1]):
        if mapa[r,c] == 1:
            przeszkody.append((r,c))

# funkcje g, h, f
def h_funkcja(x_cel, y_cel, x_n, y_n):
    return abs(x_cel - x_n) + abs(y_cel - y_n)

def g_funkcja(g_current):
    return g_current + 1  # koszt ruchu = 1

def f_funkcja(g,h):
    return g + h

# OPEN i CLOSED
open_list = [start]
closed_list = []

# fg_dict przechowuje g, h, f i rodzica (do odtworzenia ścieżki)
fg_dict = {start: {'g':0, 'h':h_funkcja(*finish, *start), 'f':h_funkcja(*finish, *start), 'parent': None}}

# możliwe ruchy: góra, dół, lewo, prawo
moves = [(-1,0),(1,0),(0,-1),(0,1)]

while open_list:
    current = min(open_list, key=lambda x: fg_dict[x]['f'])
    print("Current:", current, "f =", fg_dict[current]['f'])
    
    if current == finish:
        print("Cel osiągnięty!")
        path = []
        while current:
            path.append(current)
            current = fg_dict[current]['parent']
        path.reverse()
        print("Ścieżka:", path)
        
        # Wizualizacja ścieżki
        mapa_path = np.copy(mapa).astype(str)
        for r, c in path:
            if (r,c) != start and (r,c) != finish:
                mapa_path[r,c] = '*'
        mapa_path[start[0], start[1]] = 'S' # Start
        mapa_path[finish[0], finish[1]] = 'F' # Finish
        print("\nMapa ze ścieżką:")
        print(mapa_path)
        
        break

    open_list.remove(current)
    closed_list.append(current)

    for move in moves:
        neighbor = (current[0]+move[0], current[1]+move[1])
        
        # Sprawdzenie czy sąsiad jest poza granicami mapy
        if neighbor[0]<0 or neighbor[0]>=mapa.shape[0] or \
           neighbor[1]<0 or neighbor[1]>=mapa.shape[1]:
            continue

        # Sprawdzenie czy sąsiad jest przeszkodą LUB jest już na closed_list
        if neighbor in przeszkody or neighbor in closed_list:
            continue
        
        g = g_funkcja(fg_dict[current]['g'])
        h = h_funkcja(*finish, *neighbor)
        f = f_funkcja(g,h)

        if neighbor not in open_list:
            open_list.append(neighbor)
            fg_dict[neighbor] = {'g':g, 'h':h, 'f':f, 'parent': current}
        elif g < fg_dict[neighbor]['g']:
            fg_dict[neighbor]['g'] = g
            fg_dict[neighbor]['f'] = f
            fg_dict[neighbor]['parent'] = current

else: # Wykonuje się, jeśli pętla while zakończy się bez break (brak ścieżki)
    print("Nie znaleziono ścieżki do celu.")