//Kacper Jajuga, grupa: D2, kierunek: informatyka (PUW), rok I, semestr II
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

#define rozmiar 16 //stala oznaczajaca rozmiar macierzy

using namespace std;

bool wczytywanieDanych(int tab[][rozmiar], string tab_miasta[], int r);
int ustawianieMiastaStartowego(int miasto_startowe, int r);
int najkrotszaOdlegloscDoNastepnegoMiasta(int tab[][rozmiar], int r, bool odwiedzone[], int &ak_miasto, vector <int> &wek);

int main()
{
    int D[rozmiar][rozmiar], L, miasto_start, aktualne_miasto;
    vector <int> wektor;
    bool odwiedzone_miasta[rozmiar], sprawdzenie;
    string miasta[rozmiar] = {"Bial","Bydg","Gdan","Gorz","Kato","Kiel","Krak","Lubl","Lodz","Olsz","Opol","Pozn","Rzesz","Szcz","Warsz","Wroc"};
    char kolejny;
    do
    {
        L = 0;
        if (kolejny == 'T' || kolejny == 't')
        {
            wektor.erase(wektor.begin(), wektor.end());
        }
        sprawdzenie = wczytywanieDanych(D, miasta, rozmiar); //funkcja wczytywanieDanych zwroci wartosc 1, jesli wczytanie danych z pliku nie powiodlo sie, w przeciwnym wypadku zwroci 0
        if(sprawdzenie == 1)  //sprawdzam, jaka wartosc zwrocila funkcja wczytywanieDanych, jeœli jest to 0, to ignoruje instrukcje if
        {
            return 1;   //jesli zwrocona wartosc rowna sie 1, to koncze program, poniewaz nie zostaly pobrane zadne dane, na ktorych moze pracowac
        }

        miasto_start = ustawianieMiastaStartowego(miasto_start, rozmiar); //funkcja ustawianieMiastaStartowego poprosi o wprowadzenie numeru miasta, od ktorego mamy zaczac nasze obliczenia

        aktualne_miasto = miasto_start-1;   //wartosc aktualne_miasto ustawiam na o jeden mniejsza, poniewaz przeprowadzam operacje na tablicach dwuwymiarowych, w nich elementy tablicy ponumerowane sa od 0

        for (int i = 0; i < rozmiar; i++)
        {
            odwiedzone_miasta[i] = false; //w tej petli ustawiam wszystkie wartosci tablicy odwiedzone_miasta na fasle, tak aby nie znalazly sie w niej niepozadane wartosci
        }

        odwiedzone_miasta[aktualne_miasto] = true;  //ustawianie wartosci w komorce odwiedzone_miasta[aktualne_miasto] na true, tak aby program juz na starcie wiedzial, ze zostalo ono odwiedzone
        wektor.push_back(miasto_start);  //wpisywanie numeru miasta do wektora

        for (int i = 0; i < rozmiar; i++)
        {
            L += najkrotszaOdlegloscDoNastepnegoMiasta(D, rozmiar, odwiedzone_miasta, aktualne_miasto, wektor); //funkcja zwroci najkrotsza droge dla miasta, w ktorym aktualnie przebywamy i zsumuje ja w zmiennej L
        }

        cout << "Calkowita droga to: " << L << endl;  //wyswietlanie dlugosci przebytej drogi
        cout << "Droga przebyta: ";
        for (int i = 0; i <= rozmiar; i++)
        {
            cout << wektor[i] << " ";  //wyswietlanie kolejnych numerów miast, ktore odwiedzilismy
        }
        cout << "\nKolejno odwiedzone miasta: ";
        for (int i = 0; i <= rozmiar; i++)
        {
            cout << miasta[wektor[i]-1]  << " ";
        }
        cout << "\nCzy chcesz sprawdzic droge dla innego miasta startowego? (T/N)" << endl;
        cin >> kolejny;
    }
    while(kolejny=='t'||kolejny=='T');
    return 0;
}

bool wczytywanieDanych(int tab[][rozmiar], string tab_miasta[], int r)
{
    ifstream odczyt("dane.txt");
    if(odczyt.is_open() == false)
    {
        cout << "Plik nie zostal otwarty. Sprawdz czy w folderze z programem znajduje sie plik ''dane.txt'' i uruchom ponownie program." << endl;
        return 1; //zwracanie wartosci 1, jesli nie zostal otwarty plik, pozwoli to nam na stwierdzenie, ze caly program powinien sie zakonczyc, poniewaz nie mamy danych, na ktorych mozemy pracowac
    }
    else //instrukcje znajdujace sie w else pobiora z pliku dane i wyswietla je w konsoli
    {
        cout <<"      ";
        for (int i=0; i < rozmiar; i++)
        {
            cout << setw(6) << tab_miasta[i];
        }
        cout << endl;
        cout << "      ________________________________________________________________________________________________";
        cout << endl;
        for (int i=0; i < rozmiar; i++)
        {
            for (int j=0; j < rozmiar; j++)
            {
                if (j%(rozmiar-1)==0 && j!=(rozmiar-1))
                {
                    cout << setw(5) << tab_miasta[i] << "|";
                }
                odczyt >> tab[i][j];
                cout << setw(5) << tab[i][j] << " ";
                if (j%(rozmiar-1)==0 && j!=0)
                {
                    cout << endl;
                }
            }
        }
        odczyt.close();
        return 0;
    }
}

int ustawianieMiastaStartowego(int miasto_startowe, int r)
{
    do
    {
        cout << "\nPodaj numer miasta, z ktorego program ma zaczac obliczenia: ";
        cin >> miasto_startowe;
        if (miasto_startowe <= 0 || miasto_startowe > r) //sprawdzanie, czy zostala podana poprawna liczba z zakresu <1, 16>
        {
            cout << "Numer miasta musi znajdowac sie w przedziale <1, 16>" << endl;
        }
    }
    while(miasto_startowe <= 0 || miasto_startowe > r); //funkcja do...while wykonywac sie bedzie dopoki nie zostanie wprowadzona poprawna liczba z zakresu <1, 16>
    return miasto_startowe;
}

int najkrotszaOdlegloscDoNastepnegoMiasta(int tab[][rozmiar], int r, bool odwiedzone[], int &ak_miasto, vector <int> &wek)
{
    bool niekoniec = 0;
    int temp = 0;

    for(int i = 0; i < r; i++)
    {
        if(odwiedzone[i] == false)      //jesli komorka o indeksie i zawiera 0, czyli to miasto nie zostalo odwiedzone, to...
        {
            niekoniec = 1;              //... ustawiam zmienna niekoniec na 1...
            temp = tab[ak_miasto][i];   //... i do zmiennej temp przypisuje wartosc komorki o indeksach [ak_miasto][i]
            break;                      //koncze wykonywanie for, jedna komorka w tabeli odwiedzone z wartoscia false wystarcza
        }
    }
    if (niekoniec == 1) //jesli przynajmniej jedno miasto nie zostalo odwiedzone
    {

        for(int i = 0; i < r; i++)
        {
            if (tab[ak_miasto][i] < temp && odwiedzone[i] == false)  //jesli droga w komorce [ak_miasto][i] jest mniejsza od wartosci temp ORAZ nie odwiedzilismy miasta [i], to...
            {
                temp = tab[ak_miasto][i];                            //...przypiszmy te wartosc do temp
            }
        }

        for (int i = 0; i < r; i++)
        {
            if (temp == tab[ak_miasto][i] && odwiedzone[i] == false)    //jesli wartosc temp rowna sie drodze w komorce [ak_miasto][i] ORAZ nie odwiedzilismy miasta [i], to...
            {
                odwiedzone[i] = true;                                   //...oznaczmy miasto [i] jako odwiedzone...
                wek.push_back(i+1);                                     //...wpiszmy do wektora to odwiedzone miasto...
                ak_miasto = i;                                          //...i ustawmy miasto [i] na aktualne
            }
        }
    }
    else    //jesli odwiedzilismy wszystkie miasta, to wracamy do miasta, z ktorego zaczelismy, wiec...
    {
        temp = tab[ak_miasto][wek[0]-1];    //...przypiszmy do temp droge ktora musimy przebyc z tego miasta do miasta startowego (jest to miasto, ktore znajduje sie w pierwszej komorce wektora)...
        wek.push_back(wek[0]);              //...i wpiszmy do wektora miasto, z ktorego zaczelismy.
    }
    return temp;
}
