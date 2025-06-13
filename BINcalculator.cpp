#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

int sumaBin(int liczba1, int liczba2)
{
    int suma = liczba1 + liczba2;
    return suma;
}

int main()
{
    int liczba1,liczba2;
    cout << "Podaj liczbe bin nr1: "<<endl; 
    cin >> std::bin >> liczba1;
    cout << "Podaj liczbe bin nr2: "<<endl; 
    cin >> std::bin >> liczba2;
    int wynik = sumaBin(liczba1, liczba2);
    cout << "Suma: 0b" << std::bin << wynik << endl;
    return 0;
}