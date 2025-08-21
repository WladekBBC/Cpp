#include <iostream>
using namespace std;


class Ulamek{
    private: 
    int licznik, mianownik;

    public: 
    Ulamek (int licznik, int mianownik){
        this -> licznik = licznik;
        this -> mianownik = mianownik;
    }

    Ulamek operator+(Ulamek &u)
    {
        int l, m;
        if (mianownik == u.mianownik)
        {
            l = licznik + u.licznik;
            m = mianownik;
        }
        else   
        {
        l = (licznik * u.mianownik) + (u.licznik * mianownik);
        m = (mianownik * u.mianownik);
        }   
        return Ulamek(l,m);
    }

    Ulamek operator*(const Ulamek &u)
    {
        return Ulamek(this->licznik * u.licznik, this->mianownik + u.mianownik);
    }

    Ulamek operator-(Ulamek &u)
    {
        int l, m;
        if (mianownik == u.mianownik)
        {
            l = licznik - u.licznik;
            m = mianownik;
        }
        else   
        {
        l = (licznik * u.mianownik) - (u.licznik * mianownik);
        m = (mianownik * u.mianownik);
        }   
        return Ulamek(l,m);
    }

    Ulamek operator/(const Ulamek &u)
    {
        return Ulamek(this->licznik * u.mianownik, this->mianownik * u.licznik);
    }

    friend ostream &operator<<(ostream &out, const Ulamek &u) {
        out << u.licznik << "/" << u.mianownik;
        return out;
    }
};

int main(){
    Ulamek u1(1,2), u2(1,2);
    cout<<u1+u2<<endl;
    cout<<u1*u2<<endl;
    cout<<u1-u2<<endl;
    cout<<u1/u2<<endl;

};