#include <iostream>
using namespace std;

int main (){
    int a, b;   
    char znak; 
    cout << "Podaj liczbe A: "<<endl; 
    cin >> a;
    cout << "Podaj liczbe B: "<<endl; 
    cin >> b;
    cout << "Podaj znak : "<<endl;
    cin >> znak;
    float wynik;

    switch (znak) {
        case '+':
            wynik = a + b;
            cout <<"Wynik to : "<<endl;
            cout <<wynik<<endl;
            break;
        case '*':
            wynik = a * b;
            cout <<"Wynik to : ";
            cout <<wynik<<endl;
            break;
        case '-':
            wynik = a - b;
            cout <<"Wynik to : "<<endl;
            cout <<wynik<<endl;
            break;

        case '/':
            wynik = a/b;
            cout <<"Wynik to : "<<endl;
            cout <<wynik<<endl;
            break;
    }
    return 0;
}