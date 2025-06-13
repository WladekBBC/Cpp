#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

int sumaHex(int liczba1, int liczba2)
{
    int suma = liczba1 + liczba2;
    return suma;
}

int main()
{
    int liczba1,liczba2;
    cout << "Podaj liczbe hex nr1: "<<endl; 
    cin >> std::hex >> liczba1;
    cout << "Podaj liczbe hex nr2: "<<endl; 
    cin >> std::hex >> liczba2;
    int wynik = sumaHex(liczba1, liczba2);
    cout << "Suma: 0x" << std::hex << wynik << endl;
    return 0;
}