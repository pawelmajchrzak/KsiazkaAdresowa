#include <iostream>
#include <windows.h>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Kontakt
{
    int id;
    string imie, nazwisko, numerTelefonu, email, adres;
};

int wczytajIloscKontaktowZPliku(vector <Kontakt> &kontakty, Kontakt nowaOsoba)
{
    string linia;
    int nr_linii = 1;
    int iloscOsob = 0;
    fstream plik;
    plik.open("KsiazkaAdresowa.txt",ios::in);

    if(plik.good()==false)
    {
        return 0;
    }
    else
    {
        while (getline(plik,linia))
        {
            if (linia=="")
            {
                iloscOsob--;
                break;
            }
            int poczatekDanej=0;
            string tymczasowaKieszen[6];
            int nrZmiennej=0;
            for (int i=0; i<linia.length(); i++)
            {
                if (linia[i] == '|')
                {
                    tymczasowaKieszen[nrZmiennej] = linia.substr(poczatekDanej,i-poczatekDanej);
                    nrZmiennej++;
                    poczatekDanej = i+1;
                }
            }
            kontakty.push_back (nowaOsoba);
            kontakty[iloscOsob].id = atoi(tymczasowaKieszen[0].c_str());
            kontakty[iloscOsob].imie = tymczasowaKieszen[1];
            kontakty[iloscOsob].nazwisko = tymczasowaKieszen[2];
            kontakty[iloscOsob].numerTelefonu = tymczasowaKieszen[3];
            kontakty[iloscOsob].email = tymczasowaKieszen[4];
            kontakty[iloscOsob].adres = tymczasowaKieszen[5];

            iloscOsob++;
        }
        if (iloscOsob == -1)
            iloscOsob++;
    }
    plik.close();
    return iloscOsob;
}


void zapiszKontaktdoPliku(string imie,string nazwisko,string numerTelefonu,string email,string adres,int IdOstatniegoKontaktu)
{
    fstream plik;
    plik.open("KsiazkaAdresowa.txt",ios::out|ios::app);
    plik<<IdOstatniegoKontaktu+1<< "|";
    plik<<imie<< "|";
    plik<<nazwisko<< "|";
    plik<<numerTelefonu<< "|";
    plik<<email<< "|";
    plik<<adres<< "|"<< endl;
    plik.close();
}



int dodanieNowegoKontaktu (vector <Kontakt> &kontakty,int iloscKontaktow, Kontakt nowaOsoba, int &IdOstatniegoKontaktu)
{
    system("cls");
    cout << "Tworzenie nowego kontaku"<< endl<< endl;
    string imie, nazwisko, numerTelefonu, email, adres;
    cout << "Podaj imie: ";
    cin >> imie;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    cout << "Podaj numer telefonu: ";
    cin.clear();
    cin.sync();
    getline(cin,numerTelefonu);
    cout << "Podaj numer email: ";
    cin >> email;
    cout << "Podaj adres zamieszkania: ";
    cin.clear();
    cin.sync();
    getline(cin,adres);

    zapiszKontaktdoPliku(imie, nazwisko, numerTelefonu, email, adres, IdOstatniegoKontaktu);

    kontakty.push_back (nowaOsoba);
    kontakty[iloscKontaktow].imie = imie;
    kontakty[iloscKontaktow].nazwisko = nazwisko;
    kontakty[iloscKontaktow].numerTelefonu = numerTelefonu;
    kontakty[iloscKontaktow].email = email;
    kontakty[iloscKontaktow].adres = adres;
    kontakty[iloscKontaktow].id = IdOstatniegoKontaktu+1;
    cout <<endl<< "Nowy kontakt zostal dodany do ksiazki adresowej!"<<endl;
    Sleep (1500);
    IdOstatniegoKontaktu++;
    return iloscKontaktow+1;
}


void wyswietlKontakt (vector <Kontakt> kontakty,int numerKontaktu)
{
    cout << "Id: ";
    cout << kontakty[numerKontaktu].id<< "| ";
    cout << kontakty[numerKontaktu].imie<< " ";
    cout << kontakty[numerKontaktu].nazwisko<< " tel. ";
    cout << kontakty[numerKontaktu].numerTelefonu<< " ";
    cout << kontakty[numerKontaktu].email<< " ";
    cout << kontakty[numerKontaktu].adres<< endl;
}


void szukanieKontaktu(vector <Kontakt> kontakty,int iloscKontaktow);

void szukaniePoImieniu(vector <Kontakt> kontakty,int iloscKontaktow)
{
    string imie;
    int parametrIstnieniaOsobODanymImieniu = 0;

    system("cls");
    cout << "Wyszukiwarka kontaktow"<< endl<< endl;
    cout << "Podaj imie: ";
    cin >> imie;
    cout << endl;

    for (int i=0; i<=iloscKontaktow; i++)
    {
        if(kontakty[i].imie == imie)
        {
            wyswietlKontakt (kontakty,i);
            parametrIstnieniaOsobODanymImieniu++;
        }
    }

    if (parametrIstnieniaOsobODanymImieniu == 0)
    {
        cout << "Brak Wynikow" << endl ;
    }

    cout << endl << "1. Powrot do menu glownego" << endl;
    cout << "2. Zmien dane wyszukiwania" << endl;

        char wybor;
    cin >> wybor;

    if (wybor == '1')
    {
        return;
    }
    else if (wybor == '2')
    {
        szukanieKontaktu(kontakty,iloscKontaktow);
    }
}


void szukaniePoNazwisku(vector <Kontakt> kontakty,int iloscKontaktow)
{
    string nazwisko;
    int parametrIstnieniaOsobODanymNazwisku = 0;

    system("cls");
    cout << "Wyszukiwarka kontaktow"<< endl<< endl;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    cout << endl;

    for (int i=0; i<=iloscKontaktow; i++)
    {
        if(kontakty[i].nazwisko == nazwisko)
        {
            wyswietlKontakt (kontakty,i);
            parametrIstnieniaOsobODanymNazwisku++;
        }
    }

    if (parametrIstnieniaOsobODanymNazwisku == 0)
    {
        cout << "Brak Wynikow" << endl ;
    }

    cout << endl << "1. Powrot do menu glownego" << endl;
    cout << "2. Zmien dane wyszukiwania" << endl;

    char wybor;
    cin >> wybor;

    if (wybor == '1')
    {
        return;
    }
    else if (wybor == '2')
    {
        szukanieKontaktu(kontakty,iloscKontaktow);
    }
}


void szukanieKontaktu(vector <Kontakt> kontakty,int iloscKontaktow)
{
    system("cls");
    cout << "1. Szukaj po imieniu" << endl;
    cout << "2. Szukaj po nazwisku" << endl << endl;
    cout << "0. Powrot do menu glownego" << endl << endl;
    cout << "Twoj wybor: ";

    char wybor;

    while (1)
    {
        cin >> wybor;
        if (wybor == '1')
        {
            szukaniePoImieniu(kontakty,iloscKontaktow);
            return;
        }
        else if (wybor == '2')
        {
            szukaniePoNazwisku(kontakty,iloscKontaktow);
            return;
        }
        else if (wybor == '0')
        {
            return;
        }
        else
            cout << endl << "Blad wyboru! Sprobuj jeszcze raz: ";
    }
}


void wyswietlenieWszystkichKontaktow(vector <Kontakt> kontakty,int iloscKontaktow)
{
    cout << endl;
    for (int i=0; i<iloscKontaktow; i++)
    {
            wyswietlKontakt (kontakty,i);
    }

    cout << endl << "1. Powrot do menu glownego" << endl;
    cout << "2. Zakonczenie programu" << endl << endl;
    cout << "Twoj wybor: ";
    char wybor;
    cin >> wybor;

    if (wybor == '1')
    {
        return;
    }
    else if (wybor == '2')
    {
        exit(0);
    }
}

void edytujDaneOsoby(vector <Kontakt> &kontakty,int iloscKontaktow)
{
    system("cls");
    int Id;
    int numerKontaktu = -1;
    cout << "Podaj nr Id osoby, ktora chcesz edytowac";

    cout << endl<< endl<< "Spis kontaktow:"<< endl;

    for (int i=0; i<iloscKontaktow; i++)
    {
            wyswietlKontakt (kontakty,i);
    }

    cout << endl;
    cout << "0. Powrot do menu glownego" << endl << endl;
    cout << "Twoj wybor: ";

    while (1)
    {

    cin >> Id;
    if (Id == 0)
        return;

    for (int j=0; j<iloscKontaktow; j++)
    {
        if (Id == kontakty[j].id)
            numerKontaktu = j;
    }
    if (numerKontaktu == -1)
        cout << endl << "Blad wyboru! Sprobuj jeszcze raz: ";
    else
        break;
    }
    system("cls");

    wyswietlKontakt (kontakty,numerKontaktu);

    cout << endl << "Co chcialbys zmienic:" << endl;

    cout << "1 - imie" << endl;
    cout << "2 - nazwisko" << endl;
    cout << "3 - numer telefonu" << endl;
    cout << "4 - email" << endl;
    cout << "5 - adres" << endl;
    cout << "6 - powrot do menu" << endl;

    string zmienionaDana;
    char wybor;
    while(1)
    {
        cin >> wybor;
        switch (wybor)
        {
        case '1':
            cout << "Podaj nowe imie: ";
            cin >> zmienionaDana;
            kontakty[numerKontaktu].imie = zmienionaDana;
            cout << endl << "Zmiana zosta³a zapisana!";
            Sleep (1500);
            return;
            break;
        case '2':
            cout << "Podaj nowe nazwisko: ";
            cin >> zmienionaDana;
            kontakty[numerKontaktu].nazwisko = zmienionaDana;
            cout << endl << "Zmiana zosta³a zapisana!";
            Sleep (1500);
            return;
            break;
        case '3':
            cout << "Podaj nowy numer telefonu: ";
            cin.clear();
            cin.sync();
            getline(cin,zmienionaDana);
            kontakty[numerKontaktu].numerTelefonu = zmienionaDana;
            cout << endl << "Zmiana zosta³a zapisana!";
            Sleep (1500);
            return;
            break;
        case '4':
            cout << "Podaj nowy email: ";
            cin >> zmienionaDana;
            kontakty[numerKontaktu].email = zmienionaDana;
            cout << endl << "Zmiana zosta³a zapisana!";
            Sleep (1500);
            return;
            break;
        case '5':
            cout << "Podaj nowy adres: ";
            cin.clear();
            cin.sync();
            getline(cin,zmienionaDana);
            kontakty[numerKontaktu].adres = zmienionaDana;
            cout << endl << "Zmiana zosta³a zapisana!";
            Sleep (1500);
            return;
            break;
        case '6':
            return;
            break;
        default:
            cout << "Nie ma takiej opcji w menu!" << endl;
            cout << "Wybierz liczbe w zakresu od 1 do 6" << endl;
        }
    }
    return;
}

void zapiszZmianyDoPliku(vector <Kontakt> kontakty,int iloscKontaktow)
{
    fstream plik;
    plik.open("KsiazkaAdresowa.txt",ios::out|ios::trunc);

    for (int i=0; i<iloscKontaktow; i++)
    {
        plik<<kontakty[i].id<< "|";
        plik<<kontakty[i].imie<< "|";
        plik<<kontakty[i].nazwisko<< "|";
        plik<<kontakty[i].numerTelefonu<< "|";
        plik<<kontakty[i].email<< "|";
        plik<<kontakty[i].adres<< "|"<< endl;
    }
    plik.close();
}

void usunKontakt(vector <Kontakt> &kontakty,int &iloscKontaktow)
{
    system("cls");
    int Id;
    int numerKontaktu = -1;
    cout << "Wybierz nr Id osoby, ktora chcesz usunac";

    cout << endl<< endl<< "Spis kontaktow:"<< endl;
    for (int i=0; i<iloscKontaktow; i++)
    {
            wyswietlKontakt (kontakty,i);
    }
    cout << endl;
    cout << "0. Powrot do menu glownego" << endl << endl;
    cout << "Twoj wybor: ";
    while (1)
    {
        cin >> Id;
        if (Id == 0)
        return;

        for (int i=0; i<iloscKontaktow; i++)
        {
            if (Id == kontakty[i].id)
                numerKontaktu = i;
        }
        if (numerKontaktu == -1)
            cout << endl << "Blad wyboru! Sprobuj jeszcze raz: ";
        else
            break;

    }
    system("cls");

    wyswietlKontakt (kontakty,numerKontaktu);
    cout << endl<< endl<< "Czy napewno chcesz ten kontakt usunac? (t/n)"<< endl;
    string wybor;
    while (1)
    {
    cin >> wybor;
    transform(wybor.begin(),wybor.end(),wybor.begin(),::tolower);
    if ( wybor == "t")
    {
        for (int j=numerKontaktu; j<iloscKontaktow-1; j++)
        {
            kontakty[j].imie            = kontakty[j+1].imie;
            kontakty[j].nazwisko        = kontakty[j+1].nazwisko;
            kontakty[j].numerTelefonu   = kontakty[j+1].numerTelefonu;
            kontakty[j].email           = kontakty[j+1].email;
            kontakty[j].adres           = kontakty[j+1].adres;
            kontakty[j].id              = kontakty[j+1].id;
        }
        kontakty.pop_back();
        iloscKontaktow--;
        cout << "Usunieto kontakt!";
        Sleep (1500);
        return;
    }
    else if ( wybor == "n")
        return;
    else
        cout << "Wybierz t lub n" << endl;
    }
}


int main()
{
    vector <Kontakt> kontakty;
    Kontakt nowaOsoba;
    int idWyswietlonegoKontaktu = 0;
    int iloscKontaktow = wczytajIloscKontaktowZPliku(kontakty,nowaOsoba);
    int IdOstatniegoKontaktu;
    if (iloscKontaktow != 0)
        IdOstatniegoKontaktu = kontakty[iloscKontaktow-1].id;
    else
        IdOstatniegoKontaktu = 0;

        char wybor;

    while(1)
    {
        system("cls");
        cout << "1. Dodaj nowy kontakt" << endl;
        cout << "2. Wyszukaj kontakt" << endl;
        cout << "3. Wyswietl wszyskie moje kontakty" << endl;
        cout << "4. Edytuj kontakt" << endl;
        cout << "5. Usun kontakt" << endl;
        cout << "9. Zakoncz program" << endl <<endl;
        cout << "Twoj wybor: ";
        cin >> wybor;

        if (wybor == '1')
        {
            kontakty.push_back (nowaOsoba);
            iloscKontaktow = dodanieNowegoKontaktu (kontakty, iloscKontaktow, nowaOsoba, IdOstatniegoKontaktu);
        }
        else if (wybor == '2')
        {
            szukanieKontaktu(kontakty,iloscKontaktow);
        }
        else if (wybor == '3')
        {
            system ("cls");
            wyswietlenieWszystkichKontaktow(kontakty,iloscKontaktow);
        }
        else if (wybor == '4')
        {
            edytujDaneOsoby(kontakty,iloscKontaktow);
            zapiszZmianyDoPliku(kontakty,iloscKontaktow);
        }
        else if (wybor == '5')
        {
            usunKontakt(kontakty,iloscKontaktow);
            zapiszZmianyDoPliku(kontakty,iloscKontaktow);
        }
        else if (wybor == '9')
        {
            exit(0);
        }
    }
    return 0;
}
