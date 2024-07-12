#include <iostream>


using namespace std;
int main ()
{   
    int a, b; //tworzymy zmienne   
    int wynik_mn, wynik_dod, wynik_od; //tworzymy zmienną   
    float wynik_dziel;
    cout << "Podaj liczbe: "; //wypisujemy komunikat
    cin >> a; //wczytujemy liczbę wprowadzoną z klawiatury    
    cout << "Podaj liczbe: "; //wypisujemy komunikat
    cin >> b;  //wczytujemy liczbę wprowadzoną z klawiatury    
    wynik_dod = a+b; //obliczamy sumę
    wynik_mn = a * b;
    wynik_od = a - b;
    wynik_dziel = a/b;
    cout << "Suma podanych liczby wynosi: ";
    cout << wynik_dod <<endl;
    cout << "Iloczyn podanych liczby wynosi: ";
    cout << wynik_mn <<endl;
    cout << "Roznica podanych liczby wynosi: ";
    cout << wynik_od <<endl;
    cout << "Iloraz podanych liczby wynosi: ";
    cout << wynik_dziel <<endl; 
    return 0;
}