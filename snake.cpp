#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <fstream>


#include <deque>

#define WIDTH 70
#define HEIGHT 15

using namespace std;

COORD w;

int rx, ry;
int x0=14,y0=1, xo, yo;
int petla=0;
int lvl=100;
int z=1;
int dlugosc0=1;
int wybor=0;

int xp[100]={WIDTH/2};
int yp[100]={HEIGHT/2};

bool dl=false;
bool zapis=false;

enum Kierunek {UP,DOWN,RIGHT,LEFT} kierunek;

deque <char> x, y;

void zmien(int x, int y); //ustawianie kursora
void menu();  //wyswietlanie menu
void kursor(); //rozmiar kursora
void gra();  //algorytm gry
void owoc();  //losowanie i rysowanie owocu
void dlugosc(); //zwieksza dlugosci weza
void wyb(int dl0, int dlk);  //zmienianie kursor na menu
void statystyki(); //zapisuje statystyki do pliku
void statystykiOdczyt(); //odczytuje statystyki z pliku
void wczytaj(); // ustawia dane z zapisu

int main()
{
srand(time(NULL));

SetConsoleTitle("Snake");

kursor();

while(true)
{
    petla=0;
    if(z==1)
    {
    menu();
    x0=14,y0=1;
    zmien(x0,y0);
    z=0;
    }

    wyb(1,5);

    if(y0==1 && wybor==13)
    {
       while(petla != 2)
       {
        gra();
       }
    }

     if(y0==3 && wybor==13)
    {
       wczytaj();
    }

    if(y0==4 && wybor==13)
    {
       statystykiOdczyt();
    }


      if(y0==5 && wybor==13)
    {
        zmien(14,10);
        return 0;
    }


    if(y0==2 && wybor==13)
    {
        petla=0;

        system("cls");

        cout<<"------------------" <<endl;
        cout<<"|   lewel 1: [ ] |" << endl;
        cout<<"|   lewel 2: [ ] |" << endl;
        cout<<"|   lewel 3: [ ] |" << endl;
        cout<<"------------------" <<endl;

        zmien(x0,y0);
        kursor();

        while(petla!=3)
        {
            wyb(1,3);

            if(x0==14 && y0==1 && wybor==13)
            {
                lvl=150;
                z=1;
                petla=3;
            }

            if(x0==14 && y0==2 && wybor==13)
            {
                 lvl=100;
                 z=1;
                 petla=3;
            }

            if(x0==14 && y0==3 && wybor==13)
            {
                lvl=50;
                z=1;
                petla=3;
            }

            if(wybor==27)
            {
                z=1;
                petla=3;
            }
          }





    }



}

}

void wczytaj()
{
    ;
}


void statystykiOdczyt()
{
fstream pliks;
pliks.open("statystyki.txt", ios::in);
if(pliks.good()==false)
{
    cout<< "nid ma pliku ze statystykami" << endl;
    system("pause");
}

system("cls");

string linia;

while(getline(pliks,linia))
{
    getline(pliks,linia);
    cout<< linia << endl;
}

pliks.close();

getch();

z=1;
}



void statystyki()
{
SYSTEMTIME st;
GetLocalTime(&st);

   int godzina = st.wHour;
   int minuta  = st.wMinute;
   int sekunda = st.wSecond;
   int milisekunda = st.wMilliseconds;
   int dzien = st.wDay;
   int miesiac = st.wMonth;
   int rok = st.wYear;

fstream plik;
plik.open("statystyki.txt", ios::out | ios::app);

plik<<godzina<<":"<<minuta<<":"<<sekunda<<"   "<<dzien<<":"<<miesiac<<":"<<rok << "   " << "maksymalna dlugosc weza: " << dlugosc0 << endl << endl;

plik.close();
plik.clear();

}


void wyb(int dl0, int dlk)
{
    wybor=0;
    wybor=getch();

    switch(wybor)
    {
    case 'w':
        if(y0 > dl0)
        {
            y0-=1;
        zmien(x0,y0);
        }
    break;

    case 's':
    if(y0 < dlk)
        {
            y0+=1;
        zmien(x0,y0);
        }
    break;
    }
}

void dlugosc()
{
if(x.front()==xo && y.front()==yo)
    {
    dlugosc0++;
    owoc();
    dl=true;
    }
}

void owoc()
{
petla=0;
while(petla != 5)
{
xo = (rand()%60)+3;
yo = (rand()%10)+3;
for(int i=0; i<x.size(); i++)
{
    if(x[i]==xo && y[i]==yo){xo = (rand()%60)+3, yo = (rand()%10)+3;}
    else petla=5;
}
}

rx=w.X, ry=w.Y;

zmien(xo,yo);
cout<< (char) 219;

zmien(rx,ry);

}


void kursor()
{
    CONSOLE_CURSOR_INFO c;
    c.dwSize=80;
    c.bVisible=TRUE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), & c);
}


void menu()
{
    system("cls");

    cout<< "------------------     |-----------------------|" << endl;
    cout<< "| GRAJ       [ ] |     |  sterowanie: w,s,a,d  |" << endl;
    cout<< "| POZIOM     [ ] |     |                       |" << endl;
    cout<< "| WCZYTAJ    [ ] |     |  wybor:  Enter        |" << endl;
    cout<< "| STATYSTYKI [ ] |     |                       |" << endl;
    cout<< "| WYJDZ      [ ] |     |  wyjscie: ESC         |" << endl;
    cout<< "------------------     |                       |" << endl;
    cout<< "                       |  zapis: klawisz 0     |" << endl;
    cout<< "                       |-----------------------|" << endl;


}


void zmien(int x, int y)
{
    w.X=x;
    w.Y=y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),w);
}



void gra()
{
    system("cls");

    for(int i=0; i<=WIDTH; i++)
        cout << (char) 178;

    cout << endl;


    for(int i=0; i<=HEIGHT; i++)
    {
    cout << (char) 178;
    zmien(WIDTH,i);
    cout << (char) 178 << endl;
    }

    for(int i=0; i<=WIDTH; i++)
        cout << (char) 178;


    x.push_front(xp[0]);
    y.push_front(yp[0]);

    zmien(x.front(),y.front());
    cout << (char) 219;

    owoc();

    while(petla != 2)
    {
        if(kbhit())
        {
            switch(getch())
            {
            case 'W':
            case 'w':
                if(kierunek != DOWN)
                {
                    kierunek=UP;
                }
            break;

            case 'S':
            case 's':
                if(kierunek != UP)
                {
                    kierunek=DOWN;
                }
            break;

            case 'D':
            case 'd':
                if(kierunek != LEFT)
                {
                    kierunek=RIGHT;
                }
            break;

            case 'A':
            case 'a':
                if(kierunek != RIGHT)
                {
                    kierunek=LEFT;
                }
            break;

            case 27:
                    petla=2;
                    z=1;
                    system("cls");
                    zapis=true;

            break;
            }
        }

            x.push_front(x.front());
            y.push_front(y.front());

            switch(kierunek)
            {
            case UP:
            y.front()--;
            break;

            case DOWN:
            y.front()++;
            break;

            case LEFT:
            x.front()--;
            break;

            case RIGHT:
            x.front()++;
            break;
            }


            zmien(x.front(),y.front());
            if(x.front()==0){x.front()=69, kierunek=LEFT;}
            if(x.front()==70){x.front()=1, kierunek=RIGHT;}
            if(y.front()==0){y.front()=15, kierunek=UP;}
            if(y.front()==16){y.front()=1, kierunek=DOWN;}
            zmien(x.front(),y.front());

            cout << (char) 219;

            dlugosc();

            zmien(x.back(),y.back());
            cout << (char) 32;

            if(dl==false)
            {
                x.pop_back();
                y.pop_back();
            }
            dl=false;

                for(int i=1; i<x.size(); i++)
            {
                if(x.front()== x[i] && y.front()==y[i])
                {
                    petla=2;
                    z=1;
                    statystyki();
                    dlugosc0=1;
                    system("cls");
                    zmien(WIDTH/2,HEIGHT/2);
                    x.clear(), y.clear();
                    cout << "KONIEC GRY!" << endl << endl<< endl;
                    system("pause");
                }
            }


            Sleep(lvl);

    }
}