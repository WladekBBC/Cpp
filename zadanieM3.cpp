#include <iostream>
using namespace std;

int main()
{
    int j;
    cout << "Podaj liczbe z ktorej startujemy\n";
    cin >> j;
    for(;j <= 20; j++)
    {
        if(j % 2 == 0)
        {
            cout << j << endl;
        }
    }
    return 0;
}