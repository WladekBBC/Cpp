#include <iostream>
using namespace std;

int funkcja(int n, int *tab)
{
    for(int i = 0; i < 20;i++)
    {
        if(n == *(tab + i))
        {
            return n;
        }
    }
    return 0;
}

int main()
{
    int tab[20] = {1,2,3,4,5,6,7,8,9,0,10};
    if(funkcja(1,tab))
    {
        cout << "znaleziono" << endl;
    }
    else
    {
        cout << "nie znaleziono" << endl;
    }
    return 0;
}